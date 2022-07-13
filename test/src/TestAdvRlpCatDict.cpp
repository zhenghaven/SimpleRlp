// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

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

GTEST_TEST(TestAdvRlpCatDict, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestAdvRlpCatDict, Transform)
{
	using TF = TransformCatDict;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val1"),
			SimpleObjects::String("key2"),
			SimpleObjects::String("val2"),
		};
		SimpleObjects::Dict expOut = {
			std::make_pair(SimpleObjects::String("key1"),
				SimpleObjects::String("val1")),
			std::make_pair(SimpleObjects::String("key2"),
				SimpleObjects::String("val2")),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(output, expOut);
	}

	// Correct - key in bytes
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::Bytes({ 0x00U, 0x01U, }),
			SimpleObjects::String("val1"),
			SimpleObjects::Bytes({ 0x00U, 0x02U, }),
			SimpleObjects::String("val2"),
		};
		SimpleObjects::Dict expOut = {
			std::make_pair(SimpleObjects::Bytes({ 0x00U, 0x01U, }),
				SimpleObjects::String("val1")),
			std::make_pair(SimpleObjects::Bytes({ 0x00U, 0x02U, }),
				SimpleObjects::String("val2")),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(output, expOut);
	}

	// Incorrect - not unique
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val1"),
			SimpleObjects::String("key2"),
			SimpleObjects::String("val2"),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val3"),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect - out of order
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val1"),
			SimpleObjects::String("key3"),
			SimpleObjects::String("val3"),
			SimpleObjects::String("key2"),
			SimpleObjects::String("val2"),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect - not even number of items
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val1"),
			SimpleObjects::String("key2"),
			SimpleObjects::String("val2"),
			SimpleObjects::String("key3"),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect - non-hashable key
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::List(),
			SimpleObjects::String("val1"),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			SimpleObjects::TypeError);
	}

	// Incorrect - non-comparable keys
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x22U, }),
			SimpleObjects::String("key1"),
			SimpleObjects::String("val1"),
			SimpleObjects::Bytes({ 0x00U, 0x02U, }),
			SimpleObjects::String("val1"),
		};
		EXPECT_THROW(TF()(0, std::move(testList)),
			SimpleObjects::UnsupportedOperation);
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
			SimpleObjects::Bytes({ 0x22U, 0x00U, }),
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
		0xF8U, 0x99U,
			0x22U,
			0xC8U,
				0x82U, // string - "key1"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x31U,
			0xC8U, // [0] bytes
				0x00U,
				0x86U,
					0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
			0xC8U,
				0x82U, // string - "key2"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x32U,
			0xC1U, // [1] null
				0x01U,
			0xC8U,
				0x82U, // string - "key3"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x33U,
			0xC1U, // [2] false
				0x02U,
			0xC8U,
				0x82U, // string - "key4"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x34U,
			0xC1U, // [3] true
				0x03U,
			0xC8U,
				0x82U, // string - "key5"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x35U,
			0xC9U, // [4] integer - uint32_t
				0x83U,
					0x04U, 0x02U, 0x00U,
				0x84U,
					0x12U, 0x34U, 0x56U, 0x78U,
			// float
			0xC8U,
				0x82U, // string - "key6"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x36U,
			0xC8U, // [5] string - "val6"
				0x82U,
					0x08U, 0x00U,
				0x84U,
					0x76U, 0x61U, 0x6CU, 0x36U,
			0xC8U,
				0x82U, // string - "key7"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x37U,
			0xC7U, // [6] Array
				0x20U,
				0xC5U,
					0x00U,
					0x83U,
						0x12U, 0x34U, 0x56U,
			0xC8U,
				0x82U, // string - "key8"
					0x08U, 0x00U,
				0x84U,
					0x6BU, 0x65U, 0x79U, 0x38U,
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

static SimpleObjects::Dict GetExpectedObj()
{
	return SimpleObjects::Dict({
		std::make_pair(
			SimpleObjects::String("key1"),
			SimpleObjects::Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, })
		),
		std::make_pair(
			SimpleObjects::String("key2"),
			SimpleObjects::Null()
		),
		std::make_pair(
			SimpleObjects::String("key3"),
			SimpleObjects::Bool(false)
		),
		std::make_pair(
			SimpleObjects::String("key4"),
			SimpleObjects::Bool(true)
		),
		std::make_pair(
			SimpleObjects::String("key5"),
			SimpleObjects::UInt32(0x78563412U)
		),
		std::make_pair(
			SimpleObjects::String("key6"),
			SimpleObjects::String("val6")
		),

		std::make_pair(
			SimpleObjects::String("key7"),
			SimpleObjects::List({
				SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, }),
			})
		),
		std::make_pair(
			SimpleObjects::String("key8"),
			SimpleObjects::Dict({
				std::make_pair(SimpleObjects::String("key1"), SimpleObjects::String("val1")),
				std::make_pair(SimpleObjects::String("key2"), SimpleObjects::String("val2")),
			})
		),
	});
}

GTEST_TEST(TestAdvRlpCatDict, Parser)
{
	// Correct
	{
		auto input = GetExpectedAdvRlp();
		auto expOut = GetExpectedObj();

		auto actOut = CatDictParser().Parse(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatDict, Writer)
{
	// Correct
	{
		auto input = GetExpectedObj();
		auto expOut = GetExpectedAdvRlp();

		auto actOut = GenericWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatDict, Consistency)
{
	{
		auto inputAdvRlp = GetExpectedAdvRlp();
		auto decoded = CatDictParser().Parse(inputAdvRlp);
		auto encoded = GenericWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}

