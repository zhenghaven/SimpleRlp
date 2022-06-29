// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "../../SimpleRlp/SimpleRlp.hpp"

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
namespace AdvancedRlp
#else
namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE
#endif
{
namespace Internal
{

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimRlp = ::SimpleRlp;
#else
namespace SimRlp = ::SIMPLERLP_CUSTOMIZED_NAMESPACE;
#endif

} // namespace Internal
} // namespace AdvancedRlp
