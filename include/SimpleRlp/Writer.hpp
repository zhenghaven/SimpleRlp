// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "RlpEncoding.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _OutCtnType>
struct OutContainerConcat
{
	void operator()(_OutCtnType& dest, const _OutCtnType& src)
	{
		dest.insert(dest.end(), src.begin(), src.end());
	}
}; // struct OutContainerConcat

template<typename _BytesObjType, typename _OutCtnType>
struct WriterBytesImpl
{
	using Concatenator = OutContainerConcat<_OutCtnType>;

	inline static _OutCtnType Write(const _BytesObjType& inBytes)
	{
		using _OutCtnValType = typename _OutCtnType::value_type;
		_OutCtnType outBytes;

		const size_t inSize = inBytes.size();

		auto begin = inBytes.data();
		auto end = begin + inSize;

		outBytes.reserve(inSize);
		for (auto it = begin; it != end; ++it)
		{
			outBytes.push_back(static_cast<_OutCtnValType>(*it));
		}

		return SerializeBytes(
			RlpEncTypeCat::Bytes, outBytes, Concatenator());
	}

}; // struct WriterBytesImpl

template<typename _ListObjType, typename _OutCtnType, typename _BytesWriter>
struct WriterListImpl
{
	using Self = WriterListImpl<_ListObjType, _OutCtnType, _BytesWriter>;

	using BytesWriter = _BytesWriter;
	using Concatenator = OutContainerConcat<_OutCtnType>;

	inline static _OutCtnType Write(const _ListObjType& inList)
	{
		_OutCtnType outBytes;

		for (const auto& item : inList)
		{
			switch (item.GetCategory())
			{
			case Internal::Obj::ObjCategory::List:
			{
				auto subBytes = Self::Write(item.AsList());
				Concatenator()(outBytes, subBytes);
			}
			break;

			case Internal::Obj::ObjCategory::Bytes:
			{
				auto subBytes = BytesWriter::Write(item.AsBytes());
				Concatenator()(outBytes, subBytes);
			}
			break;

			default:
				throw SerializeTypeError(item.GetCategoryName());
			}
		}

		return SerializeBytes(RlpEncTypeCat::List, outBytes, Concatenator());
	}

}; // struct WriterListImpl

} // namespace SimpleRlp
