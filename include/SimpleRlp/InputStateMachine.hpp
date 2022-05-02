// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <iterator>
#include <limits>

#include "Exceptions.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

enum class RlpEncodeType
{
	Byte,
	BytesShort,
	BytesLong,
	ListShort,
	ListLong,
}; // enum class RlpEncodeType

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

// TODO: use std one in c++20
enum class Endian
{
// src: https://en.cppreference.com/w/cpp/types/endian
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little,
#elif defined(__ORDER_LITTLE_ENDIAN__) && \
		defined(__ORDER_BIG_ENDIAN__) && \
		defined(__BYTE_ORDER__)
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__,
#else
#	error "Cannot determine the endianness"
#endif
}; // enum class Endian

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
}; // struct ParseSizeValue<LittleEndian>

} // namespace Internal

template<typename _ValType>
inline std::pair<RlpEncodeType, _ValType>
DecodeRlpLeadingByte(_ValType val, size_t pos)
{
	// - Case 1: single byte
	if (/*(0x00U <= val)*/ (!std::numeric_limits<_ValType>::is_signed) &&
		(val <= 0x7FU))
	{
		return std::make_pair(RlpEncodeType::Byte, val);
	}
	// - Case 2: bytes within 55 bytes
	else if (/*(0x80U <= val) && */ // implicit since val > 0x7FU
			(val <= 0xB7U))
	{
		return std::make_pair(RlpEncodeType::BytesShort, (val - 0x80U));
	}
	// - Case 3: bytes longer than 55 bytes
	else if (/*(0xB8U <= val) && */ // implicit since val > 0xB7U
			(val <= 0xBFU))
	{
		return std::make_pair(RlpEncodeType::BytesLong, (val - 0xB7U));
	}
	// - Case 4: list within 55 items
	else if (/*(0xC0U <= val) && */ // implicit since val > 0xBFU
			(val <= 0xF7U))
	{
		return std::make_pair(RlpEncodeType::ListShort, (val - 0xC0U));
	}
	// - Case 5: list with more than 55 items
	else if (/* (0xF8U <= val) */ // implicit since val > 0xF7U
		Internal::IsValWithinAByte<_ValType,
			std::numeric_limits<_ValType>::digits <= 8
		>::Check(val)) /* same as (val <= 0xFFU) */
	{
		return std::make_pair(RlpEncodeType::ListLong, (val - 0xF7U));
	}

	throw ParseError("Input value should be within the range of 1 byte",
		pos);
}

/**
 * @brief The interface of a input state machine
 *
 * @tparam _ValType The type of each character value
 */
template<typename _ValType>
class InputStateMachineIf
{
public: // Static members:

	using value_type = _ValType;

	static_assert(
		std::numeric_limits<value_type>::is_integer &&
		!std::numeric_limits<value_type>::is_signed,
		"Signed input values may not work as expected");


public:

	InputStateMachineIf(value_type firstByte) :
		m_byteCount(0),
		m_data(firstByte),
		m_isEnd(false)
	{}

	// LCOV_EXCL_START
	virtual ~InputStateMachineIf() = default;
	// LCOV_EXCL_STOP

	/**
	 * @brief Get current position in terms of column in a line
	 *
	 * @return The number of lines
	 */
	size_t GetBytesCount() const
	{
		return m_byteCount;
	}

	/**
	 * @brief Get the byte value at the current position
	 *
	 * @return byte value at the current position
	 */
	value_type GetByte() const
	{
		if (!m_isEnd)
		{
			return m_data;
		}
		throw ParseError("Expecting more input data", m_byteCount);
	}

	/**
	 * @brief Get the byte value at the current position and then advance to
	 *        the next position
	 *
	 * @return value_type
	 */
	virtual value_type GetByteAndAdv()
	{
		value_type tmp = GetByte();

		std::tie(m_isEnd, m_data) = InternalNextVal();
		++m_byteCount;

		return tmp;
	}

protected:

	virtual std::pair<bool, value_type> InternalNextVal() = 0;

private:

	size_t m_byteCount;
	value_type m_data;
	bool m_isEnd;

}; // class InputStateMachineIf



/**
 * @brief An implementation of InputStateMachine interface that accepts an
 *        input iterator
 *        NOTE: this implementation will advance to the next position without
 *        checking for the end of input; so it is expected to either have a
 *        input string that is unlikely to end (e.g. console), or to stop
 *        getting next charactor right when the string ends
 *
 * @tparam _InputItType The type of the input iterator
 */
template<typename _InputItType>
class InputIteratorStateMachine :
	public InputStateMachineIf<
		typename std::iterator_traits<_InputItType>::value_type>
{
public: // static members:

	using value_type = typename std::iterator_traits<_InputItType>::value_type;
	using Base = InputStateMachineIf<value_type>;
	using Self = InputIteratorStateMachine<_InputItType>;

public:

	InputIteratorStateMachine(_InputItType it):
		Base::InputStateMachineIf(*m_it),
		m_it(it)
	{}

	// LCOV_EXCL_START
	virtual ~InputIteratorStateMachine() = default;
	// LCOV_EXCL_STOP

protected:

	virtual std::pair<bool, value_type> InternalNextVal() override
	{
		++m_it;
		return std::make_pair(false, *m_it);
	}

private:

	_InputItType m_it;

}; // class InputIteratorStateMachine


/**
 * @brief An implementation of InputStateMachine interface that accepts an
 *        forward iterator
 *        NOTE: this implementation will check for the end of the string
 *        before advancing to the next position; thus, an *end* iterator is
 *        required.
 *        If the caller is getting the next charater when the end of input
 *        string is reached, a ParseError exception will be thrown
 *
 * @tparam _ForwardItType The type of the forward iterator
 */
template<typename _ForwardItType>
class ForwardIteratorStateMachine :
	public InputStateMachineIf<
		typename std::iterator_traits<_ForwardItType>::value_type>
{
public: // static members:

	using value_type = typename std::iterator_traits<_ForwardItType>::value_type;
	using Base = InputStateMachineIf<value_type>;
	using Self = ForwardIteratorStateMachine<_ForwardItType>;

public:

	ForwardIteratorStateMachine(_ForwardItType begin, _ForwardItType end):
		Base::InputStateMachineIf(GetFirstByte(begin, end)),
		m_begin(begin),
		m_end(end)
	{}

	// LCOV_EXCL_START
	virtual ~ForwardIteratorStateMachine() = default;
	// LCOV_EXCL_STOP

protected:

	virtual std::pair<bool, value_type> InternalNextVal() override
	{
		// Check if it's already at the end since previous call
		if (m_begin == m_end)
		{
			return std::make_pair(true, value_type());
		}

		++m_begin;

		// check if it's at the end now
		if (m_begin == m_end)
		{
			return std::make_pair(true, value_type());
		}
		else
		{
			return std::make_pair(false, *m_begin);
		}
	}

private:

	static value_type GetFirstByte(_ForwardItType begin, _ForwardItType end)
	{
		if (begin != end)
		{
			return *begin;
		}
		throw ParseError("Expecting more input data", 0 /* It's first byte */);
	}

	_ForwardItType m_begin;
	_ForwardItType m_end;

}; // class ForwardIteratorStateMachine

} // namespace SimpleRlp
