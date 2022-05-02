// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleRlp/SimpleRlp.hpp>

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
using namespace SimpleRlp;
#else
using namespace SIMPLERLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestRlpEthHeader, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

namespace
{

static constexpr uint8_t sk_ethHeaders_01[] =
{
	// sizeSize: 2 bytes, size: 532, total: 1 + 2 + 532 = 535
	0XF9U, 0X02U, 0X14U, 0XA0U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0XA0U, 0X1DU, 0XCCU, 0X4DU,
	0XE8U, 0XDEU, 0XC7U, 0X5DU, 0X7AU, 0XABU, 0X85U, 0XB5U, 0X67U, 0XB6U,
	0XCCU, 0XD4U, 0X1AU, 0XD3U, 0X12U, 0X45U, 0X1BU, 0X94U, 0X8AU, 0X74U,
	0X13U, 0XF0U, 0XA1U, 0X42U, 0XFDU, 0X40U, 0XD4U, 0X93U, 0X47U, 0X94U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0XA0U, 0XD7U, 0XF8U, 0X97U, 0X4FU, 0XB5U, 0XACU, 0X78U, 0XD9U, 0XACU,
	0X09U, 0X9BU, 0X9AU, 0XD5U, 0X01U, 0X8BU, 0XEDU, 0XC2U, 0XCEU, 0X0AU,
	0X72U, 0XDAU, 0XD1U, 0X82U, 0X7AU, 0X17U, 0X09U, 0XDAU, 0X30U, 0X58U,
	0X0FU, 0X05U, 0X44U, 0XA0U, 0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU,
	0X55U, 0XA6U, 0XFFU, 0X83U, 0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU,
	0X5BU, 0X48U, 0XE0U, 0X1BU, 0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U,
	0X2FU, 0XB5U, 0XE3U, 0X63U, 0XB4U, 0X21U, 0XA0U, 0X56U, 0XE8U, 0X1FU,
	0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U, 0X45U, 0XE6U, 0X92U,
	0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU, 0X99U, 0X6CU, 0XADU,
	0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U, 0XB4U, 0X21U, 0XB9U,
	0X01U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X85U, 0X04U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X80U, 0X82U, 0X13U, 0X88U, 0X80U, 0X80U,
	0XA0U, 0X11U, 0XBBU, 0XE8U, 0XDBU, 0X4EU, 0X34U, 0X7BU, 0X4EU, 0X8CU,
	0X93U, 0X7CU, 0X1CU, 0X83U, 0X70U, 0XE4U, 0XB5U, 0XEDU, 0X33U, 0XADU,
	0XB3U, 0XDBU, 0X69U, 0XCBU, 0XDBU, 0X7AU, 0X38U, 0XE1U, 0XE5U, 0X0BU,
	0X1BU, 0X82U, 0XFAU, 0XA0U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X88U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X42U,
};

static constexpr uint8_t sk_ethHeaders_02[] =
{
	// sizeSize: 2 bytes, size: 529, total: 1 + 2 + 529 = 532
	0XF9U, 0X02U, 0X11U, 0XA0U, 0XD4U, 0XE5U, 0X67U, 0X40U, 0XF8U, 0X76U,
	0XAEU, 0XF8U, 0XC0U, 0X10U, 0XB8U, 0X6AU, 0X40U, 0XD5U, 0XF5U, 0X67U,
	0X45U, 0XA1U, 0X18U, 0XD0U, 0X90U, 0X6AU, 0X34U, 0XE6U, 0X9AU, 0XECU,
	0X8CU, 0X0DU, 0XB1U, 0XCBU, 0X8FU, 0XA3U, 0XA0U, 0X1DU, 0XCCU, 0X4DU,
	0XE8U, 0XDEU, 0XC7U, 0X5DU, 0X7AU, 0XABU, 0X85U, 0XB5U, 0X67U, 0XB6U,
	0XCCU, 0XD4U, 0X1AU, 0XD3U, 0X12U, 0X45U, 0X1BU, 0X94U, 0X8AU, 0X74U,
	0X13U, 0XF0U, 0XA1U, 0X42U, 0XFDU, 0X40U, 0XD4U, 0X93U, 0X47U, 0X94U,
	0X05U, 0XA5U, 0X6EU, 0X2DU, 0X52U, 0XC8U, 0X17U, 0X16U, 0X18U, 0X83U,
	0XF5U, 0X0CU, 0X44U, 0X1CU, 0X32U, 0X28U, 0XCFU, 0XE5U, 0X4DU, 0X9FU,
	0XA0U, 0XD6U, 0X7EU, 0X4DU, 0X45U, 0X03U, 0X43U, 0X04U, 0X64U, 0X25U,
	0XAEU, 0X42U, 0X71U, 0X47U, 0X43U, 0X53U, 0X85U, 0X7AU, 0XB8U, 0X60U,
	0XDBU, 0XC0U, 0XA1U, 0XDDU, 0XE6U, 0X4BU, 0X41U, 0XB5U, 0XCDU, 0X3AU,
	0X53U, 0X2BU, 0XF3U, 0XA0U, 0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU,
	0X55U, 0XA6U, 0XFFU, 0X83U, 0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU,
	0X5BU, 0X48U, 0XE0U, 0X1BU, 0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U,
	0X2FU, 0XB5U, 0XE3U, 0X63U, 0XB4U, 0X21U, 0XA0U, 0X56U, 0XE8U, 0X1FU,
	0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U, 0X45U, 0XE6U, 0X92U,
	0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU, 0X99U, 0X6CU, 0XADU,
	0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U, 0XB4U, 0X21U, 0XB9U,
	0X01U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
	0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X85U, 0X03U,
	0XFFU, 0X80U, 0X00U, 0X00U, 0X01U, 0X82U, 0X13U, 0X88U, 0X80U, 0X84U,
	0X55U, 0XBAU, 0X42U, 0X24U, 0X99U, 0X47U, 0X65U, 0X74U, 0X68U, 0X2FU,
	0X76U, 0X31U, 0X2EU, 0X30U, 0X2EU, 0X30U, 0X2FU, 0X6CU, 0X69U, 0X6EU,
	0X75U, 0X78U, 0X2FU, 0X67U, 0X6FU, 0X31U, 0X2EU, 0X34U, 0X2EU, 0X32U,
	0XA0U, 0X96U, 0X9BU, 0X90U, 0X0DU, 0XE2U, 0X7BU, 0X6AU, 0XC6U, 0XA6U,
	0X77U, 0X42U, 0X36U, 0X5DU, 0XD6U, 0X5FU, 0X55U, 0XA0U, 0X52U, 0X6CU,
	0X41U, 0XFDU, 0X18U, 0XE1U, 0XB1U, 0X6FU, 0X1AU, 0X12U, 0X15U, 0XC2U,
	0XE6U, 0X6FU, 0X59U, 0X88U, 0X53U, 0X9BU, 0XD4U, 0X97U, 0X9FU, 0XEFU,
	0X1EU, 0XC4U,
};

}

GTEST_TEST(TestRlpEthHeader, EthHeader_01)
{
	SimpleObjects::List expEthHeader_01 = {
		// ParentHash
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U,
		}),
		// UncleHash
		SimpleObjects::Bytes({
			0X1DU, 0XCCU, 0X4DU, 0XE8U, 0XDEU, 0XC7U, 0X5DU, 0X7AU, 0XABU, 0X85U,
			0XB5U, 0X67U, 0XB6U, 0XCCU, 0XD4U, 0X1AU, 0XD3U, 0X12U, 0X45U, 0X1BU,
			0X94U, 0X8AU, 0X74U, 0X13U, 0XF0U, 0XA1U, 0X42U, 0XFDU, 0X40U, 0XD4U,
			0X93U, 0X47U,
		}),
		// Coinbase
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
		}),
		// Root
		SimpleObjects::Bytes({
			0XD7U, 0XF8U, 0X97U, 0X4FU, 0XB5U, 0XACU, 0X78U, 0XD9U, 0XACU, 0X09U,
			0X9BU, 0X9AU, 0XD5U, 0X01U, 0X8BU, 0XEDU, 0XC2U, 0XCEU, 0X0AU, 0X72U,
			0XDAU, 0XD1U, 0X82U, 0X7AU, 0X17U, 0X09U, 0XDAU, 0X30U, 0X58U, 0X0FU,
			0X05U, 0X44U,
		}),
		// TxHash
		SimpleObjects::Bytes({
			0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U,
			0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU,
			0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U,
			0XB4U, 0X21U,
		}),
		// ReceiptHash
		SimpleObjects::Bytes({
			0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U,
			0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU,
			0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U,
			0XB4U, 0X21U,
		}),
		// Bloom
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
		}),
		// Difficulty
		SimpleObjects::Bytes({
			0X04U, 0X00U, 0X00U, 0X00U, 0X00U,
		}),
		// Number
		SimpleObjects::Bytes({
		}),
		// GasLimit
		SimpleObjects::Bytes({
			0X13U, 0X88U,
		}),
		// GasUsed
		SimpleObjects::Bytes({
		}),
		// Time
		SimpleObjects::Bytes({
		}),
		// Extra
		SimpleObjects::Bytes({
			0X11U, 0XBBU, 0XE8U, 0XDBU, 0X4EU, 0X34U, 0X7BU, 0X4EU, 0X8CU, 0X93U,
			0X7CU, 0X1CU, 0X83U, 0X70U, 0XE4U, 0XB5U, 0XEDU, 0X33U, 0XADU, 0XB3U,
			0XDBU, 0X69U, 0XCBU, 0XDBU, 0X7AU, 0X38U, 0XE1U, 0XE5U, 0X0BU, 0X1BU,
			0X82U, 0XFAU,
		}),
		// MixDigest
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U,
		}),
		// Nonce
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X42U,
		}),
	};

	ListParser parser;
	SimpleObjects::Object res;
	EXPECT_NO_THROW(res = parser.Parse(
		std::vector<uint8_t>(
			std::begin(sk_ethHeaders_01), std::end(sk_ethHeaders_01))
	));

	EXPECT_EQ(res, expEthHeader_01);
}

GTEST_TEST(TestRlpEthHeader, EthHeader_02)
{

	SimpleObjects::List expEthHeader_02 = {
		// ParentHash
		SimpleObjects::Bytes({
			0XD4U, 0XE5U, 0X67U, 0X40U, 0XF8U, 0X76U, 0XAEU, 0XF8U, 0XC0U, 0X10U,
			0XB8U, 0X6AU, 0X40U, 0XD5U, 0XF5U, 0X67U, 0X45U, 0XA1U, 0X18U, 0XD0U,
			0X90U, 0X6AU, 0X34U, 0XE6U, 0X9AU, 0XECU, 0X8CU, 0X0DU, 0XB1U, 0XCBU,
			0X8FU, 0XA3U,
		}),
		// UncleHash
		SimpleObjects::Bytes({
			0X1DU, 0XCCU, 0X4DU, 0XE8U, 0XDEU, 0XC7U, 0X5DU, 0X7AU, 0XABU, 0X85U,
			0XB5U, 0X67U, 0XB6U, 0XCCU, 0XD4U, 0X1AU, 0XD3U, 0X12U, 0X45U, 0X1BU,
			0X94U, 0X8AU, 0X74U, 0X13U, 0XF0U, 0XA1U, 0X42U, 0XFDU, 0X40U, 0XD4U,
			0X93U, 0X47U,
		}),
		// Coinbase
		SimpleObjects::Bytes({
			0X05U, 0XA5U, 0X6EU, 0X2DU, 0X52U, 0XC8U, 0X17U, 0X16U, 0X18U, 0X83U,
			0XF5U, 0X0CU, 0X44U, 0X1CU, 0X32U, 0X28U, 0XCFU, 0XE5U, 0X4DU, 0X9FU,
		}),
		// Root
		SimpleObjects::Bytes({
			0XD6U, 0X7EU, 0X4DU, 0X45U, 0X03U, 0X43U, 0X04U, 0X64U, 0X25U, 0XAEU,
			0X42U, 0X71U, 0X47U, 0X43U, 0X53U, 0X85U, 0X7AU, 0XB8U, 0X60U, 0XDBU,
			0XC0U, 0XA1U, 0XDDU, 0XE6U, 0X4BU, 0X41U, 0XB5U, 0XCDU, 0X3AU, 0X53U,
			0X2BU, 0XF3U,
		}),
		// TxHash
		SimpleObjects::Bytes({
			0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U,
			0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU,
			0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U,
			0XB4U, 0X21U,
		}),
		// ReceiptHash
		SimpleObjects::Bytes({
			0X56U, 0XE8U, 0X1FU, 0X17U, 0X1BU, 0XCCU, 0X55U, 0XA6U, 0XFFU, 0X83U,
			0X45U, 0XE6U, 0X92U, 0XC0U, 0XF8U, 0X6EU, 0X5BU, 0X48U, 0XE0U, 0X1BU,
			0X99U, 0X6CU, 0XADU, 0XC0U, 0X01U, 0X62U, 0X2FU, 0XB5U, 0XE3U, 0X63U,
			0XB4U, 0X21U,
		}),
		// Bloom
		SimpleObjects::Bytes({
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
			0X00U, 0X00U, 0X00U, 0X00U, 0X00U, 0X00U,
		}),
		// Difficulty
		SimpleObjects::Bytes({
			0X03U, 0XFFU, 0X80U, 0X00U, 0X00U,
		}),
		// Number
		SimpleObjects::Bytes({
			0x01U
		}),
		// GasLimit
		SimpleObjects::Bytes({
			0x13U, 0x88U
		}),
		// GasUsed
		SimpleObjects::Bytes({
		}),
		// Time
		SimpleObjects::Bytes({
			0X55U, 0XBAU, 0X42U, 0X24U,
		}),
		// Extra
		SimpleObjects::Bytes({
			0X47U, 0X65U, 0X74U, 0X68U, 0X2FU, 0X76U, 0X31U, 0X2EU, 0X30U, 0X2EU,
			0X30U, 0X2FU, 0X6CU, 0X69U, 0X6EU, 0X75U, 0X78U, 0X2FU, 0X67U, 0X6FU,
			0X31U, 0X2EU, 0X34U, 0X2EU, 0X32U,
		}),
		// MixDigest
		SimpleObjects::Bytes({
			0X96U, 0X9BU, 0X90U, 0X0DU, 0XE2U, 0X7BU, 0X6AU, 0XC6U, 0XA6U, 0X77U,
			0X42U, 0X36U, 0X5DU, 0XD6U, 0X5FU, 0X55U, 0XA0U, 0X52U, 0X6CU, 0X41U,
			0XFDU, 0X18U, 0XE1U, 0XB1U, 0X6FU, 0X1AU, 0X12U, 0X15U, 0XC2U, 0XE6U,
			0X6FU, 0X59U,
		}),
		// Nonce
		SimpleObjects::Bytes({
			0X53U, 0X9BU, 0XD4U, 0X97U, 0X9FU, 0XEFU, 0X1EU, 0XC4U,
		}),
	};

	ListParser parser;
	SimpleObjects::Object res;
	EXPECT_NO_THROW(res = parser.Parse(
		std::vector<uint8_t>(
			std::begin(sk_ethHeaders_02), std::end(sk_ethHeaders_02))
	));

	EXPECT_EQ(res, expEthHeader_02);
}
