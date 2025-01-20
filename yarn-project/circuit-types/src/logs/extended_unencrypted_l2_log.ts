import { BufferReader } from '@aztec/foundation/serialize';
import { bufferToHex, hexToBuffer } from '@aztec/foundation/string';
import { type FieldsOf } from '@aztec/foundation/types';

import isEqual from 'lodash.isequal';
import { z } from 'zod';

import { LogId } from './log_id.js';
import { UnencryptedL2Log } from './unencrypted_l2_log.js';

/**
 * Represents an individual unencrypted log entry extended with info about the block and tx it was emitted in.
 * TODO(#8945): Currently only used for contract class logs. When these are fields, delete this class.
 */
export class ExtendedUnencryptedL2Log {
  constructor(
    /** Globally unique id of the log. */
    public readonly id: LogId,
    /** The data contents of the log. */
    public readonly log: UnencryptedL2Log,
  ) {}

  static random() {
    return new ExtendedUnencryptedL2Log(LogId.random(), UnencryptedL2Log.random());
  }

  static get schema() {
    return z
      .object({
        id: LogId.schema,
        log: UnencryptedL2Log.schema,
      })
      .transform(ExtendedUnencryptedL2Log.from);
  }

  static from(fields: FieldsOf<ExtendedUnencryptedL2Log>) {
    return new ExtendedUnencryptedL2Log(fields.id, fields.log);
  }

  /**
   * Serializes log to a buffer.
   * @returns A buffer containing the serialized log.
   */
  public toBuffer(): Buffer {
    return Buffer.concat([this.id.toBuffer(), this.log.toBuffer()]);
  }

  /**
   * Serializes log to a string.
   * @returns A string containing the serialized log.
   */
  public toString(): string {
    return bufferToHex(this.toBuffer());
  }

  /**
   * Serializes log to a human readable string.
   * @returns A human readable representation of the log.
   */
  public toHumanReadable(): string {
    return `${this.id.toHumanReadable()}, ${this.log.toHumanReadable()}`;
  }

  /**
   * Checks if two ExtendedUnencryptedL2Log objects are equal.
   * @param other - Another ExtendedUnencryptedL2Log object to compare with.
   * @returns True if the two objects are equal, false otherwise.
   */
  public equals(other: ExtendedUnencryptedL2Log): boolean {
    return isEqual(this, other);
  }

  /**
   * Deserializes log from a buffer.
   * @param buffer - The buffer or buffer reader containing the log.
   * @returns Deserialized instance of `Log`.
   */
  public static fromBuffer(buffer: Buffer | BufferReader): ExtendedUnencryptedL2Log {
    const reader = BufferReader.asReader(buffer);

    const logId = LogId.fromBuffer(reader);
    const log = UnencryptedL2Log.fromBuffer(reader);

    return new ExtendedUnencryptedL2Log(logId, log);
  }

  /**
   * Deserializes `ExtendedUnencryptedL2Log` object from a hex string representation.
   * @param data - A hex string representation of the log.
   * @returns An `ExtendedUnencryptedL2Log` object.
   */
  public static fromString(data: string): ExtendedUnencryptedL2Log {
    return ExtendedUnencryptedL2Log.fromBuffer(hexToBuffer(data));
  }
}
