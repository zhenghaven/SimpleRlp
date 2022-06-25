# Specification for Advanced RLP

## Introduction

The RLP encoding format is able to encode a series of bytes and lists that
contain a series of bytes or another list.
The resulting binary data is deterministic, thus, the same message content
should always produce the same hash.
However, it only supports very limited data types.

To support more data types, we introduce the formal definition of
*Advanced RLP*,
which is a message encoding format supporting various data types built on top of
the traditional RLP.

## Overview

![Encoding Format Overview](./AdvRlpOverview.svg)

## Categories of Data Types

|   CAT ID (Hex)    | CAT ID (Hex)|  Category Name  |       Short Description       |
|-------------------|-------------|-----------------|-------------------------------|
| **Primitive data types**                                                          |
|[`0x00`](#cat-0x00)|`0b000 00000`|       RLP       | Regular RLP data              |
|[`0x01`](#cat-0x01)|`0b000 00001`|       Null      | Null/None                     |
|[`0x02`](#cat-0x02)|`0b000 00010`|      False      | Boolean - false               |
|[`0x03`](#cat-0x03)|`0b000 00011`|       True      | Boolean - true                |
|[`0x04`](#cat-0x04)|`0b000 00100`|     Integer     | Integer value                 |
|[`0x05`](#cat-0x05)|`0b000 00101`|      Float      | Floating point value          |
|[`0x08`](#cat-0x08)|`0b000 01000`|      String     | Character string              |
| **Composite data types**                                                          |
|[`0x20`](#cat-0x20)|`0b001 00000`|      Array      | Array of primitive types      |
|[`0x22`](#cat-0x22)|`0b001 00010`|    Dictionary   | Key-Value pairs               |
|[`0x23`](#cat-0x23)|`0b001 00011`|Static Dictionary| Dictionary w/ static mapping  |

### CAT ID reasoning

- All CAT ID has the pattern of `0b000 xxxxx` is given to the primitive types
  - So it can support at most 32 different categories of primitive data types
  - and up to 224 different categories of composite data types
- Boolean value of true and false are given their on CAT ID so that they can be
  quickly de/serialized without the need for reading any extra data

## Detailed Specification for Data Types

<a id="cat-0x00"></a>

### CAT-0x00.RLP

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                           |
|-------------|-----------------|------------------------------------|
|   `0x00`    |     None        | regular RLP encoded data in binary |

#### Comments

The data types supported by the regular RLP is still very useful to us,
thus, we dedicated CAT ID `0x00` to indicate the encoded data is a
regular RLP data.

<a id="cat-0x01"></a>

### CAT-0x01.Null

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                           |
|-------------|-----------------|------------------------------------|
|   `0x01`    |     None        | None                               |

#### Comments

- This represents `null`, which is like `null` in JSON, or `None` in python


<a id="cat-0x02"></a>

### CAT-0x02.False

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                           |
|-------------|-----------------|------------------------------------|
|   `0x02`    |     None        | None                               |


<a id="cat-0x03"></a>

### CAT-0x03.True

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                           |
|-------------|-----------------|------------------------------------|
|   `0x03`    |     None        | None                               |


<a id="cat-0x04"></a>

### CAT-0x04.Integer

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                           |
|-------------|-----------------|------------------------------------|
|   `0x04`    | 2 Bytes         | Raw data of the integer            |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                    | Possible Data | Meaning        |
|----------------------|-------------------------------|---------------|----------------|
| 0                    |Integer width; in terms of 2^x | `0x00`        | 1 byte integer |
|                      |                               | `0x01`        | 2 byte integer |
|                      |                               | `0x02`        | 4 byte integer |
|                      |                               | `0x03`        | 8 byte integer |
| 1                    |Signedness of the integer      | `0x00`        | unsigned integer|
|                      |                               | `0x10`        | signed positive integer |
|                      |                               | `0x11`        | signed negative integer |

#### Additional requirement
- The integer value stored in raw data is in little-endian


<a id="cat-0x05"></a>

### CAT-0x05.Float (Draft, work-in-progress)

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                             |
|-------------|-----------------|--------------------------------------|
|   `0x05`    | 2 Bytes         | Biased Exponent & Normalized Mantisa |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                    | Possible Data | Meaning        |
|----------------------|-------------------------------|---------------|----------------|
| 0                    |Floating point value width;    | `0x02`        | 4 byte         |
|                      |  in terms of 2^x              | `0x03`        | 8 byte         |
| 1                    |Signedness of the value        | `0x00`        | positive       |
|                      |                               | `0x01`        | negative       |

#### Comments

- The basic idea is to follow the IEEE Standard 754
[[1]](https://www.geeksforgeeks.org/ieee-standard-754-floating-point-numbers).
- The floating number will be broken into
  - 1 bit of sign
  - some bits of Biased Exponent
  - some bits of Normalized Mantisa
- And then serialized into the raw data field
- When deserializing, these components will be read from the raw data field
  and assembled into a floating value
- This data type is not planned to be implemented in the early release


<a id="cat-0x08"></a>

### CAT-0x08.String

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Raw Data                             |
|-------------|-----------------|--------------------------------------|
|   `0x08`    | 9 Byte          | Char string data                     |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                    | Possible Data | Meaning        |
|----------------------|-------------------------------|---------------|----------------|
| 0                    |The width of the char value;   | `0x00`        | 1 byte         |
|                      |  in terms of 2^x              |               |                |
| 1 - 8                |The length of the string;      | N/A           |                |
|                      |  8 byte unsigned integer;     |               |                |
|                      |  little-endian                |               |                |


#### Additional requirement

- All strings are assumed to be encoded in UTF

#### Comments

- Currently, we only support UTF-8
  - More UTF (e.g., UTF-16, UTF-32) encoding could be added in future
    when needed


<a id="cat-0x20"></a>

### CAT-0x20.Array

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Following Data                             |
|-------------|-----------------|--------------------------------------------|
|   `0x20`    | 8 Byte          | A sequence of primitive or composite data  |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                      | Possible Data | Meaning  |
|----------------------|---------------------------------|---------------|----------|
| 0 - 8                |The number of items in the array;| N/A           |          |
|                      |  8 byte unsigned integer;       |               |          |
|                      |  little-endian                  |               |          |


<a id="cat-0x22"></a>

### CAT-0x22.Dictionary

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Following Data                             |
|-------------|-----------------|--------------------------------------------|
|   `0x22`    | 8 Byte          | A sequence of primitive or composite data  |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                    | Possible Data | Meaning  |
|----------------------|-------------------------------|---------------|----------|
| 0 - 8                |The number of K-V pairs in the | N/A           |          |
|                      |  dictionary;                  |               |          |
|                      |  8 byte unsigned integer;     |               |          |
|                      |  little-endian                |               |          |

#### Additional requirements

- The keys must be hashable and `<` comparable
- Each key must be unique in the dictionary
- The K-V pairs must be ordered based on the key from min to max
- The data after the *type spec bytes* in the *encoding layout* is having the
  format of:
  - `key1`, `value1`, `key2`, `value2`, `key3`, `value3`, ...


<a id="cat-0x23"></a>

### CAT-0x23.StaticDictionary

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

#### Encoding layout

| CAT ID Byte | Type Spec Bytes | Following Data                             |
|-------------|-----------------|--------------------------------------------|
|   `0x23`    | 8 Byte          | A sequence of primitive or composite data  |

#### Type spec bytes

| Offset<br>(in bytes) | Definition                 | Possible Data | Meaning  |
|----------------------|----------------------------|---------------|----------|
| 0 - 8                |The number of values in the | N/A           |          |
|                      |  dictionary;               |               |          |
|                      |  8 byte unsigned integer;  |               |          |
|                      |  little-endian             |               |          |

#### Additional requirements

- In a static dictionary, the mapping from key to value type is known in
  compile-time
  - This is very similar to the Ethereum header, where the developers know the
    *ParentHash* is in the first place and its data type is a SHA-3 hash,
    and *sha3Uncle* is in the second place and its data type is a SHA-3 hash,
    etc.
  - Thus, in the serialized data, we can omit their "key" values, and assume
    the deserializing program has them hardcoded
  - And their order is also hardcoded by the program
- The data after the *type spec bytes* in the *encoding layout* is having the
  format of:
  - `value1`, `value2`, `value3`, ...
