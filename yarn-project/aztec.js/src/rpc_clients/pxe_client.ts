import { createSafeJsonRpcClient, makeFetch } from '@aztec/foundation/json-rpc/client';
import { protocolContractTreeRoot } from '@aztec/protocol-contracts';
import { type PXE, PXESchema } from '@aztec/stdlib/interfaces/client';
import { type ComponentsVersions, getVersioningResponseHandler } from '@aztec/stdlib/versioning';

/**
 * Creates a JSON-RPC client to remotely talk to PXE.
 * @param url - The URL of the PXE.
 * @param fetch - The fetch implementation to use.
 * @returns A JSON-RPC client of PXE.
 */
export function createPXEClient(
  url: string,
  versions: Partial<ComponentsVersions> = {},
  fetch = makeFetch([1, 2, 3], false),
): PXE {
  return createSafeJsonRpcClient<PXE>(url, PXESchema, {
    namespaceMethods: 'pxe',
    fetch,
    onResponse: getVersioningResponseHandler({
      l2ProtocolContractsTreeRoot: protocolContractTreeRoot.toString(),
      ...versions,
    }),
  });
}
