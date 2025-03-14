import { Blob } from '@aztec/blob-lib';
import { BLOBS_PER_BLOCK, BLOB_PUBLIC_INPUTS } from '@aztec/constants';
import { timesParallel } from '@aztec/foundation/collection';
import { randomInt } from '@aztec/foundation/crypto';
import { Fr } from '@aztec/foundation/fields';

import { BlobPublicInputs, BlockBlobPublicInputs } from './blob_public_inputs.js';
import { makeBlobPublicInputs, makeBlockBlobPublicInputs } from './testing.js';

describe('BlobPublicInputs', () => {
  let blobPI: BlobPublicInputs;

  beforeAll(() => {
    blobPI = makeBlobPublicInputs(randomInt(1000));
  });

  it('serializes to buffer and deserializes it back', () => {
    const buffer = blobPI.toBuffer();
    const res = BlobPublicInputs.fromBuffer(buffer);
    expect(res).toEqual(blobPI);
  });

  it('converts correctly from Blob class', async () => {
    const blob = await Blob.fromFields(Array(400).fill(new Fr(3)));
    const converted = BlobPublicInputs.fromBlob(blob);
    expect(converted.z).toEqual(blob.challengeZ);
    expect(Buffer.from(converted.y.toString(16), 'hex')).toEqual(blob.evaluationY);
    expect(converted.kzgCommitment).toEqual(blob.commitmentToFields());
    expect(converted.commitmentToBuffer()).toEqual(blob.commitment);
  });

  it('serializes to field array and deserializes it back', () => {
    const fieldArray = blobPI.toFields();
    const res = BlobPublicInputs.fromFields(fieldArray);
    expect(res).toEqual(blobPI);
  });

  // NB: In noir, blob.y is represented as a BigNum = 3x Fr fields. In ts, we use bigint for ease of calcs.
  it('number of fields matches constant', () => {
    const fields = blobPI.toFields();
    expect(fields.length).toBe(BLOB_PUBLIC_INPUTS);
  });
});

describe('BlockBlobPublicInputs', () => {
  let blobPI: BlockBlobPublicInputs;

  beforeAll(() => {
    blobPI = makeBlockBlobPublicInputs(randomInt(1000));
  });

  it('serializes to buffer and deserializes it back', () => {
    const buffer = blobPI.toBuffer();
    const res = BlockBlobPublicInputs.fromBuffer(buffer);
    expect(res).toEqual(blobPI);
  });

  it('converts correctly from Blob class', async () => {
    const blobs = await timesParallel(BLOBS_PER_BLOCK, i => Blob.fromFields(Array(400).fill(new Fr(i + 1))));
    const converted = BlockBlobPublicInputs.fromBlobs(blobs);
    converted.inner.forEach((blobPI, i) => {
      expect(blobPI.z).toEqual(blobs[i].challengeZ);
      expect(Buffer.from(blobPI.y.toString(16), 'hex')).toEqual(blobs[i].evaluationY);
      expect(blobPI.kzgCommitment).toEqual(blobs[i].commitmentToFields());
      expect(blobPI.commitmentToBuffer()).toEqual(blobs[i].commitment);
    });
  });

  it('serializes to field array and deserializes it back', () => {
    const fieldArray = blobPI.toFields();
    const res = BlockBlobPublicInputs.fromFields(fieldArray);
    expect(res).toEqual(blobPI);
  });

  // NB: In noir, blob.y is represented as a BigNum = 3x Fr fields. In ts, we use bigint for ease of calcs.
  it('number of fields matches constant', () => {
    const fields = blobPI.toFields();
    expect(fields.length).toBe(BLOB_PUBLIC_INPUTS * BLOBS_PER_BLOCK);
  });
});
