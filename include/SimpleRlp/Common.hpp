// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once


#if __cplusplus >= 202002L
#include <version>
#else
#include <ciso646>
#endif // __cplusplus >= 202002L

#ifdef __cpp_lib_endian
#include <bit>
#endif


#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

/**
 * @brief The categories of RLP encoding types
 *
 */
enum class RlpEncTypeCat
{
	Bytes,
	List
}; // enum class RlpEncTypeCat

/**
 * @brief The RLP encoding types
 *
 */
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

template<RlpEncTypeCat _Cat>
struct RlpEncTypeCatName;

template<>
struct RlpEncTypeCatName<RlpEncTypeCat::Bytes>
{
	static const char* value()
	{
		return "Bytes";
	}
}; // struct RlpEncTypeCatName<RlpEncTypeCat::Bytes>

template<>
struct RlpEncTypeCatName<RlpEncTypeCat::List>
{
	static const char* value()
	{
		return "List";
	}
}; // struct RlpEncTypeCatName<RlpEncTypeCat::List>

} // namespace Internal

enum class Endian
{
#ifdef __cpp_lib_endian
    little =
		static_cast<std::underlying_type_t<std::endian> >(std::endian::little),
    big    =
		static_cast<std::underlying_type_t<std::endian> >(std::endian::big),
    native =
		static_cast<std::underlying_type_t<std::endian> >(std::endian::native),
// src: https://en.cppreference.com/w/cpp/types/endian
#elif defined(_WIN32)
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
#	error "Cannot determine the platform endianness"
#endif
}; // enum class Endian

} // namespace SimpleRlp
