# Specification for Advanced RLP

## Introduction

The RLP encoding format is able to encode a series of bytes and lists that
contain a series of bytes or another list.
The resulting binary data is deterministic, thus, the same message content
should always produce the same hash.
However, it only supports very limited data types, such as bytes and lists, as
shown below.

```
Bytes    ::= null               # A bytes string could be empty
           | Byte               # or, only contain a single byte
           | Byte, Bytes        # or, a sequence of bytes

ListItem ::= Bytes              # The item in a list could be a byte string
           | List               # or, a nested list

List     ::= null               # A list could be empty
           | ListItem, ...      # or, contain one or more items
```

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
|[`0x00`](#cat-0x00)|`0b000 00000`|      Bytes      | Bytes string                  |
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
  - So it can support at most 32 different *categories* of primitive data types
  - and up to 224 different *categories* of composite data types
- Boolean value of true and false are given their on CAT ID so that they can be
  quickly de/serialized without the need for reading any extra data

## Detailed Specification for Data Types


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x00"></a>

### CAT-0x00.Bytes

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                           |
|-------------------------------|------------------------------------|
| `0x00`                        | regular RLP encoded *bytes*        |

#### Type Specs Definitions

- None for this category

#### Comments

The data types supported by the regular RLP is still very useful to us,
meanwhile, because of its limitation, we also introduced AdvancedRLP array
that can hold various data types.

However, supporting the regular RLP as one category in AdvancedRLP could be
ambiguous:
when the serializer receives an array/list of byte data, it can encode it
using regular RLP list or using AdvancedRLP array.
This breaks the rule of deterministic de-/serialization.

To avoid this ambiguity, AdvancedRLP only using CAT ID `0x00` to support bytes
data, and list/array-like data structure is supported by CAT ID `0x20`.


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x01"></a>

### CAT-0x01.Null

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                           |
|-------------------------------|------------------------------------|
| `0x01`                        | None                               |

#### Type Specs Definitions

- None for this category

#### Comments

- This represents `null`, which is like `null` in JSON, or `None` in python


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x02"></a>

### CAT-0x02.False

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                           |
|-------------------------------|------------------------------------|
| `0x02`                        | None                               |

#### Type Specs Definitions

- None for this category


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x03"></a>

### CAT-0x03.True

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                           |
|-------------------------------|------------------------------------|
| `0x03`                        | None                               |

#### Type Specs Definitions

- None for this category


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x04"></a>

### CAT-0x04.Integer

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                           |
|-------------------------------|------------------------------------|
| `0x04`, `0x??`, `0x??`        | Raw data of the integer            |

#### Type Specs Definitions

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


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x05"></a>

### CAT-0x05.Float (Draft, work-in-progress)

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                             |
|-------------------------------|--------------------------------------|
| `0x05`, `0x??`, `0x??`        | Biased Exponent & Normalized Mantisa |

#### Type Specs Definitions

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


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x08"></a>

### CAT-0x08.String

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Raw Data                             |
|-------------------------------|--------------------------------------|
| `0x08`, `0x??`                | Char string data                     |

#### Type Specs Definitions

| Offset<br>(in bytes) | Definition                    | Possible Data | Meaning        |
|----------------------|-------------------------------|---------------|----------------|
| 0                    |The width of the char value;   | `0x00`        | 1 byte         |
|                      |  in terms of 2^x              |               |                |

#### Additional requirement

- All strings are assumed to be encoded in UTF

#### Comments

- Currently, we only support UTF-8
  - More UTF (e.g., UTF-16, UTF-32) encoding could be added in future
    when needed
- Length of the string is depend on the size of the raw data bytes, which is
  encoded as bytes in a regular RLP

[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x20"></a>

### CAT-0x20.Array

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Data                                       |
|-------------------------------|--------------------------------------------|
| `0x20`                        | A sequence of primitive or composite data  |

#### Type Specs Definitions

- None for this category

#### Comments

- The number of items in the array depends on the number of items in the
  following data section


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x22"></a>

### CAT-0x22.Dictionary

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Data                                       |
|-------------------------------|--------------------------------------------|
| `0x22`                        | A sequence of primitive or composite data  |

#### Type Specs Definitions

- None for this category

#### Additional requirements

- Each key must be unique in the dictionary
- The keys must be hashable and `<` comparable
- The K-V pairs must be ordered based on the key from min to max
- The data section following the *Type Specs* Bytes shown in the
  *encoding layout* has the format in:
  - `key1`, `value1`, `key2`, `value2`, `key3`, `value3`, ...

#### Comments

- The number of pairs in the dictionary depends on the number of items in the
  following data section
  - The layout of keys and values in the data section is given above


[<p align='right'>Back to list of categories</p>](#categories-of-data-types)

<a id="cat-0x23"></a>

### CAT-0x23.StaticDictionary

#### Encoding layout

| *CAT ID* + *Type Specs* Bytes | Data                                       |
|-------------------------------|--------------------------------------------|
| `0x23`                        | A sequence of primitive or composite data  |

#### Type Specs Definitions

- None for this category

#### Additional requirements

- In a static dictionary, the mapping from key to value type is known in
  compile-time
  - This is very similar to the Ethereum header, where the developers know the
    *ParentHash* is in the first place and its data type is a SHA-3 hash,
    and *sha3Uncle* is in the second place and its data type is a SHA-3 hash,
    and so on.
  - Thus, in the serialized data, we can omit their "key" values, and assume
    the deserializing program has their name and order hardcoded
- The data section following the *Type Specs* Bytes shown in the
  *encoding layout* has the format in:
  - `value1`, `value2`, `value3`, ...
