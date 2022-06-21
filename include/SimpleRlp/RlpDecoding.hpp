// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <limits>
#include <utility>

#include "Common.hpp"
#include "Exceptions.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

//====================
// Decoding
//====================

namespace Internal
{

template<typename _ValType, bool _IsValTypeByte>
struct IsValWithinAByte;

template<typename _ValType>
struct IsValWithinAByte<_ValType, false>
{
	static bool Check(_ValType val)
	{
		return val <= 0xFFU;
	}
}; // struct IsValWithinAByte

template<typename _ValType>
struct IsValWithinAByte<_ValType, true>
{
	static bool Check(_ValType)
	{
		return true;
	}
}; // struct IsValWithinAByte


inline size_t DecodeSizeBytes(const uint8_t (&b)[8])
{
	uint64_t size = 0;
	std::memcpy(&size, &b[0], sizeof(uint64_t));

	return static_cast<size_t>(size);
}

template<Endian _EndianType>
struct ParseSizeValue;

template<>
struct ParseSizeValue<Endian::little>
{
	template<typename _InputFuncType>
	static size_t Parse(size_t len, size_t pos, _InputFuncType inFunc)
	{
		static constexpr size_t sk_byteInBits = 8;
		uint8_t vals[sk_byteInBits] = { 0 };

		// NOTE: len is not checked to ensure len <= 8, since this is internal
		// func
		// size_t missingLen = sk_byteInBits - len;

		for(size_t i = 0; i < len; ++i)
		{
			auto val = inFunc();
			if (!Internal::IsValWithinAByte<decltype(val),
				std::numeric_limits<decltype(val)>::digits <= 8
			>::Check(val))
			{
				throw ParseError("Invalid input value", pos + i);
			}

			vals[len - 1 - i] = static_cast<uint8_t>(val);
		}

		return DecodeSizeBytes(vals);
	}
}; // struct ParseSizeValue<Endian::little>

} // namespace Internal

namespace Internal
{

template<typename _ValType, bool isValSigned>
struct DecodeRlpLeadingByteImpl;

template<typename _ValType>
struct DecodeRlpLeadingByteImpl<_ValType, false>
{
	static std::pair<RlpEncodeType, _ValType> Decode(_ValType val, size_t pos)
	{
		// - Case 1: single byte
		if (/*(0x00U <= val) && */
			(val <= 0x7FU))
		{
			return std::make_pair(RlpEncodeType::Byte, val);
		}
		// - Case 2: bytes within 55 bytes
		else if (/*(0x80U <= val) && */ // implicit since val > 0x7FU
				(val <= 0xB7U))
		{
			return std::make_pair(RlpEncodeType::BytesShort, _ValType(val - 0x80U));
		}
		// - Case 3: bytes longer than 55 bytes
		else if (/*(0xB8U <= val) && */ // implicit since val > 0xB7U
				(val <= 0xBFU))
		{
			return std::make_pair(RlpEncodeType::BytesLong, _ValType(val - 0xB7U));
		}
		// - Case 4: list within 55 bytes
		else if (/*(0xC0U <= val) && */ // implicit since val > 0xBFU
				(val <= 0xF7U))
		{
			return std::make_pair(RlpEncodeType::ListShort, _ValType(val - 0xC0U));
		}
		// - Case 5: list with more than 55 bytes
		else if (/* (0xF8U <= val) */ // implicit since val > 0xF7U
			Internal::IsValWithinAByte<_ValType,
				std::numeric_limits<_ValType>::digits <= 8
			>::Check(val)) /* same as (val <= 0xFFU) */
		{
			return std::make_pair(RlpEncodeType::ListLong, _ValType(val - 0xF7U));
		}

		throw ParseError("Input value should be within the range of 1 byte",
			pos);
	}
}; // struct DecodeRlpLeadingByteImpl

} // namespace Internal

template<typename _ValType>
inline std::pair<RlpEncodeType, _ValType>
DecodeRlpLeadingByte(_ValType val, size_t pos)
{
	return Internal::DecodeRlpLeadingByteImpl<
		_ValType,
		std::numeric_limits<_ValType>::is_signed
	>::Decode(val, pos);
}

} // namespace SimpleRlp
