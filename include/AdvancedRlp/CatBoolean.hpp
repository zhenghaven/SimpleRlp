// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "ParserUtils.hpp"

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
namespace AdvancedRlp
#else
namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE
#endif
{


// ====================
// Parsers
// ====================


template<bool _IsTrue, typename _ListObjType>
inline void PreCheckCatBoolean(size_t pos, const _ListObjType& l)
{
	using namespace Internal::SimRlp::Internal::Obj;
	Internal::CheckRlpListTypeSizeEq(
		_IsTrue ? "CAT True" : "CAT False",
		pos,
		l,
		std::pair<std::string, ObjCategory>("Bytes", ObjCategory::Bytes)
	);

	const auto& specs = l[0].AsBytes();
	if (specs.size() != 1)
	{
		throw ParseError(
			_IsTrue ?
				"CAT True's specs bytes should be exactly 1 byte" :
				"CAT False's specs bytes should be exactly 1 byte",
			pos);
	}

	if ((_IsTrue && GetCatIdFromByte(specs[0]) == CatId::True) ||
		(!_IsTrue && GetCatIdFromByte(specs[0]) == CatId::False))
	{
		return;
	}
	else
	{
		throw ParseError(
			_IsTrue ?
				"The given RLP list is not in CAT True" :
				"The given RLP list is not in CAT False",
			pos);
	}
}


template<
	bool _IsTrue,
	typename _ListObjType,
	typename _BoolObjType>
struct TransformCatBooleanImpl
{
	using RetType = _BoolObjType;


	RetType operator()(size_t pos, _ListObjType&& l)
	{
		PreCheckCatBoolean<_IsTrue>(pos, l);

		return RetType(_IsTrue);
	}
}; // struct TransformCatBooleanImpl


using TransformCatFalse = TransformCatBooleanImpl<
	false,
	Internal::SimRlp::ListObjType,
	Internal::SimRlp::Internal::Obj::Bool>;


using TransformCatTrue = TransformCatBooleanImpl<
	true,
	Internal::SimRlp::ListObjType,
	Internal::SimRlp::Internal::Obj::Bool>;


using CatFalseParser = Internal::SimRlp::ListParserImpl<
	Internal::SimRlp::InputContainerType,
	Internal::SimRlp::ByteValType,
	Internal::SimRlp::ListObjType,
	TransformCatFalse,
	Internal::SimRlp::BytesParser,
	Internal::SimRlp::SelfParserPlaceholder>;


using CatTrueParser = Internal::SimRlp::ListParserImpl<
	Internal::SimRlp::InputContainerType,
	Internal::SimRlp::ByteValType,
	Internal::SimRlp::ListObjType,
	TransformCatTrue,
	Internal::SimRlp::BytesParser,
	Internal::SimRlp::SelfParserPlaceholder>;


// ====================
// Writers
// ====================


template<
	typename _InObjType,
	typename _OutCtnType>
struct CatBooleanWriterImpl
{
	using Self = CatBooleanWriterImpl<_InObjType, _OutCtnType>;

	using Concatenator = Internal::SimRlp::OutContainerConcat<_OutCtnType>;


	inline static _OutCtnType Write(const _InObjType& val)
	{
		Concatenator ccntr;
		_OutCtnType outBytes;

		// 1.specs
		auto catId = val.IsTrue() ?
			SerializeCatId(CatId::True) :
			SerializeCatId(CatId::False);
		outBytes.push_back(catId);

		// 2.raw data
		// N/A

		// 3.build RLP list
		return Internal::SimRlp::
			SerializeBytes(
				Internal::SimRlp::RlpEncTypeCat::List,
				outBytes,
				ccntr);
	}

}; // struct CatBooleanWriterImpl


using CatBooleanWriter =
	CatBooleanWriterImpl<
		Internal::SimRlp::Internal::Obj::RealNumBaseObj,
		Internal::SimRlp::OutputContainerType>;

} // namespace AdvancedRlp
