import { AztecAddress } from '@aztec/foundation/aztec-address';
import { EthAddress } from '@aztec/foundation/eth-address';
import { Fr } from '@aztec/foundation/fields';
import { BufferReader, FieldReader, serializeToBuffer, serializeToFields } from '@aztec/foundation/serialize';
import { type FieldsOf } from '@aztec/foundation/types';

import { inspect } from 'util';

import { GLOBAL_VARIABLES_LENGTH } from '../constants.gen.js';
import { GasFees } from './gas_fees.js';

/**
 * Global variables of the L2 block.
 */
export class GlobalVariables {
  constructor(
    /** ChainId for the L2 block. */
    public chainId: Fr,
    /** Version for the L2 block. */
    public version: Fr,
    /** Block number of the L2 block. */
    public blockNumber: Fr,
    /** Slot number of the L2 block */
    public slotNumber: Fr,
    /** Timestamp of the L2 block. */
    public timestamp: Fr,
    /** Recipient of block reward. */
    public coinbase: EthAddress,
    /** Address to receive fees. */
    public feeRecipient: AztecAddress,
    /** Global gas prices for this block. */
    public gasFees: GasFees,
  ) {}

  getSize(): number {
    return this.toBuffer().length;
  }

  static from(fields: FieldsOf<GlobalVariables>): GlobalVariables {
    return new GlobalVariables(...GlobalVariables.getFields(fields));
  }

  static empty(): GlobalVariables {
    return new GlobalVariables(
      Fr.ZERO,
      Fr.ZERO,
      Fr.ZERO,
      Fr.ZERO,
      Fr.ZERO,
      EthAddress.ZERO,
      AztecAddress.ZERO,
      GasFees.empty(),
    );
  }

  static fromBuffer(buffer: Buffer | BufferReader): GlobalVariables {
    const reader = BufferReader.asReader(buffer);
    return new GlobalVariables(
      Fr.fromBuffer(reader),
      Fr.fromBuffer(reader),
      Fr.fromBuffer(reader),
      Fr.fromBuffer(reader),
      Fr.fromBuffer(reader),
      reader.readObject(EthAddress),
      reader.readObject(AztecAddress),
      reader.readObject(GasFees),
    );
  }

  static fromJSON(obj: any): GlobalVariables {
    return new GlobalVariables(
      Fr.fromString(obj.chainId),
      Fr.fromString(obj.version),
      Fr.fromString(obj.blockNumber),
      Fr.fromString(obj.slotNumber),
      Fr.fromString(obj.timestamp),
      EthAddress.fromString(obj.coinbase),
      AztecAddress.fromString(obj.feeRecipient),
      GasFees.fromJSON(obj.gasFees),
    );
  }

  static fromFields(fields: Fr[] | FieldReader): GlobalVariables {
    const reader = FieldReader.asReader(fields);

    return new GlobalVariables(
      reader.readField(),
      reader.readField(),
      reader.readField(),
      reader.readField(),
      reader.readField(),
      EthAddress.fromField(reader.readField()),
      AztecAddress.fromField(reader.readField()),
      GasFees.fromFields(reader),
    );
  }

  static getFields(fields: FieldsOf<GlobalVariables>) {
    // Note: The order here must match the order in the HeaderLib solidity library.
    return [
      fields.chainId,
      fields.version,
      fields.blockNumber,
      fields.slotNumber,
      fields.timestamp,
      fields.coinbase,
      fields.feeRecipient,
      fields.gasFees,
    ] as const;
  }

  toBuffer() {
    return serializeToBuffer(...GlobalVariables.getFields(this));
  }

  toFields() {
    const fields = serializeToFields(...GlobalVariables.getFields(this));
    if (fields.length !== GLOBAL_VARIABLES_LENGTH) {
      throw new Error(
        `Invalid number of fields for GlobalVariables. Expected ${GLOBAL_VARIABLES_LENGTH}, got ${fields.length}`,
      );
    }
    return fields;
  }

  toJSON() {
    return {
      chainId: this.chainId.toString(),
      version: this.version.toString(),
      blockNumber: this.blockNumber.toString(),
      slotNumber: this.slotNumber.toString(),
      timestamp: this.timestamp.toString(),
      coinbase: this.coinbase.toString(),
      feeRecipient: this.feeRecipient.toString(),
      gasFees: this.gasFees.toJSON(),
    };
  }

  /**
   * A trimmed version of the JSON representation of the global variables,
   * tailored for human consumption.
   */
  toFriendlyJSON() {
    return {
      blockNumber: this.blockNumber.toNumber(),
      slotNumber: this.slotNumber.toNumber(),
      timestamp: this.timestamp.toString(),
      coinbase: this.coinbase.toString(),
      gasFees: this.gasFees.toJSON(),
    };
  }

  clone(): GlobalVariables {
    return GlobalVariables.fromBuffer(this.toBuffer());
  }

  isEmpty(): boolean {
    return (
      this.chainId.isZero() &&
      this.version.isZero() &&
      this.blockNumber.isZero() &&
      this.slotNumber.isZero() &&
      this.timestamp.isZero() &&
      this.coinbase.isZero() &&
      this.feeRecipient.isZero() &&
      this.gasFees.isEmpty()
    );
  }

  [inspect.custom]() {
    return `GlobalVariables { chainId: ${this.chainId.toString()}, version: ${this.version.toString()}, blockNumber: ${this.blockNumber.toString()}, slotNumber: ${this.slotNumber.toString()}, timestamp: ${this.timestamp.toString()}, coinbase: ${this.coinbase.toString()}, feeRecipient: ${this.feeRecipient.toString()}, gasFees: ${inspect(
      this.gasFees,
    )} }`;
  }

  public equals(other: this): boolean {
    return (
      this.chainId.equals(other.chainId) &&
      this.version.equals(other.version) &&
      this.blockNumber.equals(other.blockNumber) &&
      this.slotNumber.equals(other.slotNumber) &&
      this.timestamp.equals(other.timestamp) &&
      this.coinbase.equals(other.coinbase) &&
      this.feeRecipient.equals(other.feeRecipient) &&
      this.gasFees.equals(other.gasFees)
    );
  }
}
