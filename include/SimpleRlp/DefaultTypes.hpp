// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "BytesParser.hpp"
#include "ListParser.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

using ByteValType = uint8_t;
using InputContainerType = std::vector<uint8_t>;

using BytesParser =
	BytesParserImpl<
		InputContainerType,
		ByteValType,
		Internal::Obj::Bytes,
		TransformByteToBytes<ByteValType, Internal::Obj::Bytes>,
		TransformPassthrough,
		Internal::Obj::Object>;

using ListParser =
	ListParserImpl<
		InputContainerType,
		ByteValType,
		Internal::Obj::List,
		TransformPassthrough,
		Internal::Obj::Object,
		BytesParser,
		SelfParserPlaceholder>;

} // namespace SimpleRlp
