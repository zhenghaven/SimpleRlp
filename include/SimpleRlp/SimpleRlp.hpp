// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "DefaultTypes.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

inline RetObjType ParseRlp(const InputContainerType& inBytes)
{
	return GeneralParser().Parse(inBytes);
}

inline OutputContainerType WriteRlp(const Internal::Obj::BaseObj& obj)
{
	switch (obj.GetCategory())
	{
	case Internal::Obj::ObjCategory::Bytes:
		return WriterBytes::Write(obj.AsBytes());

	case Internal::Obj::ObjCategory::List:
		return WriterList::Write(obj.AsList());

	default:
		throw SerializeTypeError(obj.GetCategoryName());
	}
}

} // namespace SimpleRlp
