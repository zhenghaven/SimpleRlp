// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <limits>

#include "Common.hpp"
#include "Exceptions.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

//====================
// Encoding
//====================

namespace Internal
{


/**
 * @brief Encoding a primitive integer value into a RLP byte sequence.
 *
 * @tparam _IntType      The type of the input integer value
 * @tparam _EndianType   The endian type that the input integer value is in
 *                       (usually depending on the platform)
 * @tparam _IsDestSigned Is the type of each individual byte in the
 *                       *destination container* a signed value?
 *                       Currently we only support unsigned types
 *                       (e.g., array of uint8_t); thus, signed types
 *                       (e.g., array of char or int8_t) does not work
 */
template<typename _IntType, Endian _EndianType, bool _IsDestSigned>
struct EncodePrimitiveIntValue;

template<typename _IntType>
struct EncodePrimitiveIntValue<_IntType, Endian::little, false>
{
	template<typename _CtnType>
	static void Encode(_CtnType& res, const _IntType& inVal)
	{
		static constexpr size_t sk_inTypeSize = sizeof(_IntType);

		_IntType tmp = 0;
		for (size_t i = 0; i < sk_inTypeSize - 1; ++i)
		{
			tmp |= ((inVal >> (i * 8)) & 0xFFU);
			tmp <<= 8;
		}
		// The last byte should not be shifted
		tmp |= ((inVal >> ((sk_inTypeSize - 1) * 8)) & 0xFFU);

		bool writeStart = false;
		for (size_t i = 0; i < sk_inTypeSize; ++i)
		{
			if (
				!writeStart &&        // we haven't start writing (leading)
				((tmp & 0xFFU) == 0)  // this byte is 0
				)
			{
				// skip leading zeros
			}
			else
			{
				writeStart = true;
				res.push_back(static_cast<uint8_t>(tmp & 0xFFU));
			}
			tmp >>= 8;
		}
	}
}; // EncodePrimitiveIntValue<_IntType, Endian::little, false>


template<Endian _EndianType, bool _IsDestSigned>
struct EncodeSizeValue
{
	template<typename _CtnType>
	static void Encode(_CtnType& res, size_t inSize)
	{
		EncodePrimitiveIntValue<size_t, _EndianType, _IsDestSigned>::
			Encode(res, inSize);
	}
}; // struct EncodeSizeValue


template<bool _IsValSigned>
struct EncodeRlpBytesImpl;

template<>
struct EncodeRlpBytesImpl<false>
{
	static constexpr bool sk_isValSigned = false;

	template<typename _CtnType>
	static _CtnType GenLeadingBytes(RlpEncTypeCat rlpCat, size_t byteSize)
	{
		// Determine RlpEncodeType
		switch (rlpCat)
		{
		case RlpEncTypeCat::Bytes:
		{
			if (byteSize <= 55)
			{
				// RlpEncodeType::BytesShort
				_CtnType res;
				res.push_back(static_cast<uint8_t>(0x80U + byteSize));
				return res;
			}
			else
			{
				// RlpEncodeType::BytesLong
				_CtnType res;
				res.push_back(0);
				EncodeSizeValue<Endian::native, sk_isValSigned>::Encode(
					res, byteSize);
				res[0] = static_cast<uint8_t>(0xB7U + (res.size() - 1));
				return res;
			}
		}

		case RlpEncTypeCat::List:
		{
			if (byteSize <= 55)
			{
				// RlpEncodeType::ListShort
				_CtnType res;
				res.push_back(static_cast<uint8_t>(0xC0U + byteSize));
				return res;
			}
			else
			{
				// RlpEncodeType::ListLong
				_CtnType res;
				res.push_back(0);
				EncodeSizeValue<Endian::native, sk_isValSigned>::Encode(
					res, byteSize);
				res[0] = static_cast<uint8_t>(0xF7U + (res.size() - 1));
				return res;
			}
		}

		}

		throw SerializeError("Unknown RLP encoding type category was given");
	}

	template<typename _CtnType, typename _OutConcatOp>
	static _CtnType SerializeBytes(
		RlpEncTypeCat rlpCat, const _CtnType& inBytes, _OutConcatOp concatOp)
	{
		// Special case - if the input is just 1 byte
		if ((rlpCat == RlpEncTypeCat::Bytes) &&
			(inBytes.size() == 1) &&
			(inBytes[0] <= 0x7FU))
		{
			return inBytes;
		}

		auto leadBytes = GenLeadingBytes<_CtnType>(rlpCat, inBytes.size());

		concatOp(leadBytes, inBytes);

		return leadBytes;
	}
}; // struct EncodeRlpBytesImpl

} // namespace Internal


/**
 * @brief Helper function to serialize a serial of bytes or a concatenated
 *        list of bytes
 *        NOTE: this function assume the individual values in the given bytes
 *        container are in the range of 1 byte [0, 255].
 *
 * @tparam _CtnType The type of the container used for input and output
 * @tparam _OutConcatOp The type of the `concatOp` param
 *
 * @param rlpCat    The category of the given bytes;
 *                  - `RlpEncTypeCat::Bytes` means that the given bytes is
 *                    just a serial of bytes
 *                  - `RlpEncTypeCat::List` means that the given bytes is
 *                    a concatenated list of bytes
 * @param inBytes   The input bytes, which could either be a serial of bytes,
 *                  or a concatenated list of bytes
 * @param concatOp  A function used to concatenate two output container
 *                  instances
 *
 * @return serialized bytes encoded in RLP
 */
template<typename _CtnType, typename _OutConcatOp>
inline _CtnType SerializeBytes(
	RlpEncTypeCat rlpCat, const _CtnType& inBytes, _OutConcatOp concatOp)
{
	using _DestValType = typename _CtnType::value_type;
	return Internal::EncodeRlpBytesImpl<
		std::numeric_limits<_DestValType>::is_signed>::SerializeBytes(
			rlpCat, inBytes, concatOp);
}

} // namespace SimpleRlp
