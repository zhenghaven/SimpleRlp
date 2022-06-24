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
  - So it can support at most 32 different categories of data types
- Boolean value of true and false are given their on CAT ID so that they can be
  quickly de/serialized without the need for reading any extra data

## Detailed Specification for Data Types

<a id="cat-0x00"></a>

### CAT-0x00.RLP

<div style="text-align: right"><a href="#categories-of-data-types">Back to list of categories</a></div>

<a id="cat-0x01"></a>

### CAT-0x01.Null

<div style="text-align: right"><a href="#categories-of-data-types">Back to list of categories</a></div>

<a id="cat-0x02"></a>

### CAT-0x02.False

<div style="text-align: right"><a href="#categories-of-data-types">Back to list of categories</a></div>

<a id="cat-0x03"></a>

### CAT-0x03.True

<div style="text-align: right"><a href="#categories-of-data-types">Back to list of categories</a></div>
