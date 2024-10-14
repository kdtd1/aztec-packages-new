import { Fr, VerificationKeyAsFields, VerificationKeyData } from '@aztec/circuits.js';
import { poseidon2Hash } from '@aztec/foundation/crypto';

interface VkJson {
  keyAsBytes: string;
  keyAsFields: string[];
  vkHash: string;
}

export function keyJsonToVKData(json: VkJson): VerificationKeyData {
  const { keyAsBytes, keyAsFields, vkHash } = json;
  return new VerificationKeyData(
    new VerificationKeyAsFields(
      keyAsFields.map((str: string) => Fr.fromString(str)),
      Fr.fromString(vkHash),
    ),
    Buffer.from(keyAsBytes, 'hex'),
  );
}

export function hashVk(keyAsFields: Fr[]): Fr {
  return poseidon2Hash(keyAsFields);
}
