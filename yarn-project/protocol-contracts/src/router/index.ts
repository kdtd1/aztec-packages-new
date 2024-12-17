import { loadContractArtifact } from '@aztec/types/abi';
import { type NoirCompiledContract } from '@aztec/types/noir';

import RouterJson from '../../artifacts/Router.json' assert { type: 'json' };
import { makeProtocolContract } from '../make_protocol_contract.js';
import { type ProtocolContract } from '../protocol_contract.js';

export const RouterArtifact = loadContractArtifact(RouterJson as NoirCompiledContract);

let protocolContract: ProtocolContract;

/** Returns the canonical deployment of the contract. */
export function getCanonicalRouter(): ProtocolContract {
  if (!protocolContract) {
    protocolContract = makeProtocolContract('Router', RouterArtifact);
  }
  return protocolContract;
}
