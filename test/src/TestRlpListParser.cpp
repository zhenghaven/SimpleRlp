// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
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

GTEST_TEST(TestRlpListParser, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestRlpListParser, ParseCorrect)
{
	ListParser parser;

	// list - short
	{
		std::vector<uint8_t> testInput = { 0xC0U, };

		SimpleObjects::Object expRes = SimpleObjects::List();

		SimpleObjects::Object res;
		EXPECT_NO_THROW(res = parser.Parse(testInput));
		EXPECT_TRUE(res == expRes);
	}
	{
		std::vector<uint8_t> testInput = { 0xF7U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};

		auto zeroB = SimpleObjects::Bytes({ 0x00U, });
		SimpleObjects::Object expRes =  SimpleObjects::List({
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB,
		});

		SimpleObjects::Object res;
		EXPECT_NO_THROW(res = parser.Parse(testInput));
		EXPECT_TRUE(res == expRes);
	}

	// list - long
	{
		std::vector<uint8_t> testInput = { 0xF8U, 0x00U, };

		SimpleObjects::Object expRes = SimpleObjects::List();

		SimpleObjects::Object res;
		EXPECT_NO_THROW(res = parser.Parse(testInput));
		EXPECT_TRUE(res == expRes);
	}
	{
		std::vector<uint8_t> testInput = { 0xFFU,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0x00U,
			// 256 bytes
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,

			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,

			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};

		auto zeroB = SimpleObjects::Bytes({ 0x00U, });
		SimpleObjects::Object expRes = SimpleObjects::List({
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,

			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,

			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
			zeroB, zeroB, zeroB, zeroB, zeroB, zeroB,
		});

		SimpleObjects::Object res;
		EXPECT_NO_THROW(res = parser.Parse(testInput));
		EXPECT_TRUE(res == expRes);
	}

	// List - nested list
	// [[[[[[[[], ['d', 'o', 'g']]]]]]]]
	// 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xC7U, 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xC8U, 0xC7U, 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xC9U, 0xC8U, 0xC7U, 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xCAU, 0xC9U, 0xC8U, 0xC7U, 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	// 0xCBU, 0xCAU, 0xC9U, 0xC8U, 0xC7U, 0xC6U, 0xC5U, 0xC0U, 0x83U, 'd', 'o', 'g'
	{
		std::vector<uint8_t> testInput = {
			0xCBU,
				0xCAU,
					0xC9U,
						0xC8U,
							0xC7U,
								0xC6U,
									0xC5U,
										0xC0U, 0x83U, 'd', 'o', 'g',
		};

		SimpleObjects::Object expRes;
		{
			SimpleObjects::List l1 =
				{
					SimpleObjects::List(),
					SimpleObjects::Bytes({'d', 'o', 'g',}),
				};
			SimpleObjects::List l2 = { SimpleObjects::Object(std::move(l1)), };
			SimpleObjects::List l3 = { SimpleObjects::Object(std::move(l2)), };
			SimpleObjects::List l4 = { SimpleObjects::Object(std::move(l3)), };
			SimpleObjects::List l5 = { SimpleObjects::Object(std::move(l4)), };
			SimpleObjects::List l6 = { SimpleObjects::Object(std::move(l5)), };
			SimpleObjects::List l7 = { SimpleObjects::Object(std::move(l6)), };

			expRes = std::move(l7);
		}

		SimpleObjects::Object res;
		EXPECT_NO_THROW(res = parser.Parse(testInput));
		EXPECT_TRUE(res == expRes);
	}

}

GTEST_TEST(TestRlpListParser, ParseError)
{
	ListParser parser;

	// not enough data
	{
		std::vector<uint8_t> testInput = { };
		EXPECT_THROW(
			parser.Parse(testInput),
			ParseError);
	}
	{
		std::vector<uint8_t> testInput = { 0xC1U, };
		EXPECT_THROW(
			parser.Parse(testInput),
			ParseError);
	}

	// nested list, outer size doesn't match inner size
	{
		std::vector<uint8_t> testInput = { 0xC2U, 0x83U, 'd', 'o', 'g', };
		EXPECT_THROW(
			parser.Parse(testInput),
			ParseError);
	}

	// wrong type - bytes short
	{
		std::vector<uint8_t> testInput = { 0x80U, };
		EXPECT_THROW(
			parser.Parse(testInput),
			ParseError);
	}
}

GTEST_TEST(TestRlpListParser, UnknownRlpEncodeType)
{
	using _ISM = ListParser::ISMType;
	std::vector<uint8_t> testInput = {0x00U};
	_ISM ism(
		Internal::Obj::ToFrIt<true>(testInput.cbegin()),
		Internal::Obj::ToFrIt<true>(testInput.cend()));

	RlpEncodeType unknownType = static_cast<RlpEncodeType>(123);

	{
		size_t byteLeft = 0;
		EXPECT_THROW(
			GeneralParser().Parse(ism, unknownType, 0x00U, byteLeft);,
			ParseError
		);
	}
}
