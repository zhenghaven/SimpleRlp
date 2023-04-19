// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <AdvancedRlp/AdvancedRlp.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatArray, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestAdvRlpCatArray, Transform)
{
	using TF = TransformCatArray;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x20U, }),
			SimpleObjects::String("val1"),
		};
		SimpleObjects::List expOut = {
			SimpleObjects::String("val1"),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(output, expOut);
	}

	// Incorrect num of items in list
	{
		SimpleObjects::List testList = {
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x20U, 0x00U, }),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}
}

static std::vector<uint8_t> GetExpectedAdvRlp()
{
	return std::vector<uint8_t>({
		0xF8U, 0x51U,
			0x20U,
			0xC8U, // [0] bytes
				0x00U,
				0x86U,
					0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
			0xC1U, // [1] null
				0x01U,
			0xC1U, // [2] false
				0x02U,
			0xC1U, // [3] true
				0x03U,
			0xC9U, // [4] integer - uint32_t
				0x83U,
					0x04U, 0x02U, 0x00U,
				0x84U,
					0x12U, 0x34U, 0x56U, 0x78U,
			// float
			0xC8U, // [5] string - "val1"
				0x82U,
					0x08U, 0x00U,
				0x84U,
					0x76U, 0x61U, 0x6CU, 0x31U,
			0xC7U, // [6] Array
				0x20U,
				0xC5U,
					0x00U,
					0x83U,
						0x12U, 0x34U, 0x56U,
			0xE5U, // [7] Dict
				0x22U,
				0xC8U,
					0x82U, // string - "key1"
						0x08U, 0x00U,
					0x84U,
						0x6BU, 0x65U, 0x79U, 0x31U,
				0xC8U,
					0x82U, // string - "val1"
						0x08U, 0x00U,
					0x84U,
						0x76U, 0x61U, 0x6CU, 0x31U,
				0xC8U,
					0x82U, // string - "key2"
						0x08U, 0x00U,
					0x84U,
						0x6BU, 0x65U, 0x79U, 0x32U,
				0xC8U,
					0x82U, // string - "val2"
						0x08U, 0x00U,
					0x84U,
						0x76U, 0x61U, 0x6CU, 0x32U,
		});
}

static SimpleObjects::List GetExpectedObj()
{
	return SimpleObjects::List({
		SimpleObjects::Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, }),
		SimpleObjects::Null(),
		SimpleObjects::Bool(false),
		SimpleObjects::Bool(true),
		SimpleObjects::UInt32(0x78563412U),
		SimpleObjects::String("val1"),

		SimpleObjects::List({
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, }),
		}),
		SimpleObjects::Dict({
			std::make_pair(SimpleObjects::String("key1"), SimpleObjects::String("val1")),
			std::make_pair(SimpleObjects::String("key2"), SimpleObjects::String("val2")),
		}),
	});
}

GTEST_TEST(TestAdvRlpCatArray, Parser)
{
	// Correct
	{
		auto input = GetExpectedAdvRlp();
		auto expOut = GetExpectedObj();

		auto actOut = CatArrayParser().Parse(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatArray, GenericParser)
{
	// Incorrect - unkown CAT ID
	{
		std::vector<uint8_t> input = {
			0xC4U,
				0x20U,
				0xC2U,
					0x81U, // CAT ID = 0xFF
						0xFFU,
		};

		EXPECT_THROW(GenericParser().Parse(input), UnknownCatId);
	}
}

GTEST_TEST(TestAdvRlpCatArray, Writer)
{
	// Correct
	{
		auto input = GetExpectedObj();
		auto expOut = GetExpectedAdvRlp();

		auto actOut = GenericWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatArray, Consistency)
{
	{
		auto inputAdvRlp = GetExpectedAdvRlp();
		auto decoded = CatArrayParser().Parse(inputAdvRlp);
		auto encoded = GenericWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}
