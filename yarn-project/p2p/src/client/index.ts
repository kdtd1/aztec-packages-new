import type { ClientProtocolCircuitVerifier, L2BlockSource, WorldStateSynchronizer } from '@aztec/circuit-types';
import { createDebugLogger } from '@aztec/foundation/log';
import { type AztecKVStore } from '@aztec/kv-store';
import { type DataStoreConfig, createStore } from '@aztec/kv-store/utils';
import { type TelemetryClient } from '@aztec/telemetry-client';
import { NoopTelemetryClient } from '@aztec/telemetry-client/noop';

import { P2PClient } from '../client/p2p_client.js';
import { type P2PConfig } from '../config.js';
import { type AttestationPool } from '../mem_pools/attestation_pool/attestation_pool.js';
import { InMemoryAttestationPool } from '../mem_pools/attestation_pool/memory_attestation_pool.js';
import { type EpochProofQuotePool } from '../mem_pools/epoch_proof_quote_pool/epoch_proof_quote_pool.js';
import { MemoryEpochProofQuotePool } from '../mem_pools/epoch_proof_quote_pool/memory_epoch_proof_quote_pool.js';
import { type MemPools } from '../mem_pools/interface.js';
import { AztecKVTxPool, type TxPool } from '../mem_pools/tx_pool/index.js';
import { DiscV5Service } from '../service/discV5_service.js';
import { DummyP2PService } from '../service/dummy_service.js';
import { LibP2PService, createLibP2PPeerId } from '../service/index.js';
import { getPublicIp, resolveAddressIfNecessary, splitAddressPort } from '../util.js';

export * from './p2p_client.js';

export const createP2PClient = async (
  _config: P2PConfig & DataStoreConfig,
  l2BlockSource: L2BlockSource,
  proofVerifier: ClientProtocolCircuitVerifier,
  worldStateSynchronizer: WorldStateSynchronizer,
  telemetry: TelemetryClient = new NoopTelemetryClient(),
  deps: {
    txPool?: TxPool;
    store?: AztecKVStore;
    attestationPool?: AttestationPool;
    epochProofQuotePool?: EpochProofQuotePool;
  } = {},
) => {
  let config = { ..._config };
  const store = deps.store ?? (await createStore('p2p', config, createDebugLogger('aztec:p2p:lmdb')));

  const mempools: MemPools = {
    txPool: deps.txPool ?? new AztecKVTxPool(store, telemetry),
    attestationPool: deps.attestationPool ?? new InMemoryAttestationPool(telemetry),
    epochProofQuotePool: deps.epochProofQuotePool ?? new MemoryEpochProofQuotePool(telemetry),
  };

  let p2pService;

  if (_config.p2pEnabled) {
    config = await configureP2PClientAddresses(_config);

    // Create peer discovery service
    const peerId = await createLibP2PPeerId(config.peerIdPrivateKey);
    const discoveryService = new DiscV5Service(peerId, config);

    p2pService = await LibP2PService.new(
      config,
      discoveryService,
      peerId,
      mempools,
      l2BlockSource,
      proofVerifier,
      worldStateSynchronizer,
      store,
      telemetry,
    );
  } else {
    p2pService = new DummyP2PService();
  }
  return new P2PClient(store, l2BlockSource, mempools, p2pService, config.keepProvenTxsInPoolFor, telemetry);
};

async function configureP2PClientAddresses(_config: P2PConfig & DataStoreConfig): Promise<P2PConfig & DataStoreConfig> {
  const config = { ..._config };
  const {
    tcpAnnounceAddress: configTcpAnnounceAddress,
    udpAnnounceAddress: configUdpAnnounceAddress,
    queryForIp,
  } = config;

  config.tcpAnnounceAddress = configTcpAnnounceAddress
    ? await resolveAddressIfNecessary(configTcpAnnounceAddress)
    : undefined;
  config.udpAnnounceAddress = configUdpAnnounceAddress
    ? await resolveAddressIfNecessary(configUdpAnnounceAddress)
    : undefined;

  // create variable for re-use if needed
  let publicIp;

  // check if no announce IP was provided
  const splitTcpAnnounceAddress = splitAddressPort(configTcpAnnounceAddress || '', true);
  if (splitTcpAnnounceAddress.length == 2 && splitTcpAnnounceAddress[0] === '') {
    if (queryForIp) {
      publicIp = await getPublicIp();
      const tcpAnnounceAddress = `${publicIp}:${splitTcpAnnounceAddress[1]}`;
      config.tcpAnnounceAddress = tcpAnnounceAddress;
    } else {
      throw new Error(
        `Invalid announceTcpAddress provided: ${configTcpAnnounceAddress}. Expected format: <addr>:<port>`,
      );
    }
  }

  const splitUdpAnnounceAddress = splitAddressPort(configUdpAnnounceAddress || '', true);
  if (splitUdpAnnounceAddress.length == 2 && splitUdpAnnounceAddress[0] === '') {
    // If announceUdpAddress is not provided, use announceTcpAddress
    if (!queryForIp && config.tcpAnnounceAddress) {
      config.udpAnnounceAddress = config.tcpAnnounceAddress;
    } else if (queryForIp) {
      const udpPublicIp = publicIp || (await getPublicIp());
      const udpAnnounceAddress = `${udpPublicIp}:${splitUdpAnnounceAddress[1]}`;
      config.udpAnnounceAddress = udpAnnounceAddress;
    }
  }

  return config;
}
