// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "BytesParser.hpp"
#include "ListParser.hpp"
#include "GeneralParser.hpp"
#include "StaticDictParser.hpp"

#include "Writer.hpp"

#include "EthHeader.hpp"

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


//====================
// Parser
//====================

using BytesParser =
	BytesParserImpl<
		InputContainerType,
		ByteValType,
		BytesObjType,
		TransformByteToBytes<ByteValType, BytesObjType>,
		TransformPassthrough<BytesObjType> >;

template<typename _InnerBytesParser, typename _InnerListParser>
using ListParserT =
	ListParserImpl<
		InputContainerType,
		ByteValType,
		ListObjType,
		TransformPassthrough<ListObjType>,
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

template<
	typename _ParserTp,
	bool _AllowMissingItem,
	bool _AllowExtraItem,
	typename _StaticDictType = AutoPlaceholder>
using StaticDictParserT = StaticDictParserImpl<
	InputContainerType,
	ByteValType,
	_ParserTp,
	GeneralParser,
	_AllowMissingItem,
	_AllowExtraItem,
	typename std::conditional<
			std::is_same<_StaticDictType, AutoPlaceholder>::value,
			Internal::Obj::StaticDict<
				typename Internal::DParserTuple2TupleCore<_ParserTp>::type>,
			_StaticDictType
		>::type
	>;


//====================
// Writer
//====================

using WriterGeneric = WriterGenericImpl<
	OutputContainerType,
	WriterBytesImpl,
	WriterListImpl,
	WriterStaticDictImpl>;


//====================
// Ethereum
//====================

using EthHeader = EthHeaderImpl<BytesObjType>;

using EthHeaderParser = StaticDictParserT<
		Internal::EthHeaderParserTupleCore<BytesParser>,
		false,
		false,
		EthHeader>;


} // namespace SimpleRlp
