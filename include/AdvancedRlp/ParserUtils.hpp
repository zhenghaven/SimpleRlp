// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "CatId.hpp"
#include "Exceptions.hpp"

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
namespace AdvancedRlp
#else
namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE
#endif
{

namespace Internal
{

inline void CheckRlpListSizeEq(
	const std::string& catName,
	size_t pos,
	size_t expSize,
	size_t recvSize)
{
	if (recvSize != expSize)
	{
		throw ParseError(
			catName + " requires " +
			std::to_string(expSize) +
			" items in the RLP list, while " +
			std::to_string(recvSize) +
			" items were given",
			pos
		);
	}
}


template<typename _RlpListType>
inline void CheckObjCat(
	const std::string&,
	size_t,
	const _RlpListType&,
	size_t)
{
	return;
}


template<
	typename _RlpListType,
	typename _ObjCatType,
	typename... _ObjCatTypes>
inline void CheckObjCat(
	const std::string& catName,
	size_t pos,
	const _RlpListType& l,
	size_t idx,
	_ObjCatType cat0,
	_ObjCatTypes ...cats)
{
	const auto& item = l[idx];
	if (item.GetCategory() != cat0.second)
	{
		throw ParseError(
			catName +
			"'s item " +
			std::to_string(idx) +
			" should be type of " +
			cat0.first +
			", while type of " +
			item.GetCategoryName() +
			" is given",
			pos
		);
	}
	CheckObjCat(catName, pos, l, idx + 1, cats...);
}


template<
	typename _RlpListType,
	typename... _ObjCatType>
inline void CheckRlpListTypeSizeEq(
	const std::string& catName,
	size_t pos,
	const _RlpListType& l,
	_ObjCatType ...objCat)
{
	static constexpr size_t expNumItem = sizeof...(_ObjCatType);
	CheckRlpListSizeEq(catName, pos, expNumItem, l.size());

	// check object categories
	CheckObjCat(catName, pos, l, 0, objCat...);
}

} // namespace Internal

} // namespace AdvancedRlp
