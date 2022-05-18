// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "BytesParser.hpp"
#include "ListParser.hpp"
#include "GeneralParser.hpp"

#include "Writer.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

using ByteValType = uint8_t;

using InputContainerType  = std::vector<uint8_t>;
using OutputContainerType = std::vector<uint8_t>;

using RetObjType   = Internal::Obj::Object;
using BytesObjType = Internal::Obj::Bytes;
using ListObjType  = Internal::Obj::List;

using BytesBaseObjType = Internal::Obj::BytesBaseObj;
using ListBaseObjType  = Internal::Obj::ListBaseObj;

//====================
// Parser
//====================

using BytesParser =
	BytesParserImpl<
		InputContainerType,
		ByteValType,
		BytesObjType,
		TransformByteToBytes<ByteValType, BytesObjType>,
		TransformPassthrough,
		RetObjType>;

template<typename _InnerBytesParser, typename _InnerListParser>
using ListParserT =
	ListParserImpl<
		InputContainerType,
		ByteValType,
		ListObjType,
		TransformPassthrough,
		RetObjType,
		_InnerBytesParser,
		_InnerListParser>;

using ListParser = ListParserT<BytesParser, SelfParserPlaceholder>;

using GeneralParser =
	GeneralParserImpl<
		InputContainerType,
		ByteValType,
		BytesParser,
		ListParser,
		RetObjType>;

//====================
// Writer
//====================

using WriterBytes = WriterBytesImpl<BytesBaseObjType, OutputContainerType>;

using WriterList =
	WriterListImpl<ListBaseObjType, OutputContainerType, WriterBytes>;

} // namespace SimpleRlp
