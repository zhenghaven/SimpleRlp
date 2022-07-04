// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatNull.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatNull, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}


GTEST_TEST(TestAdvRlpCatNull, Transform)
{
	using TF =
		TransformCatNull<
			SimpleObjects::List,
			SimpleObjects::Null>;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x01U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Null());
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x01U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x01U, 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}
}


GTEST_TEST(TestAdvRlpCatNull, Parser)
{

	// Correct
	{
		auto output = CatNullParser().Parse(
			std::vector<uint8_t>(
				{
					0xC1U,
						0x01U,
				}));

		auto expOut = SimpleObjects::Null();

		EXPECT_EQ(output, expOut);
	}

	// Incorrect encoding - extra raw data
	{
		auto testProg = [](){
			CatNullParser().Parse(
				std::vector<uint8_t>({
					0xC2U,
						0x00U,
						0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a list
	{
		auto testProg = [](){
			CatNullParser().Parse(
				std::vector<uint8_t>({
					0xC3U,
						0x00U,
						0xC1U,
							0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a long byte
	{
		auto testProg = [](){
			CatNullParser().Parse(
				std::vector<uint8_t>({
					0xF8U, 0x3FU,
						0x01U,
						0xB8U, 0x3CU,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
							0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatNull, Writer)
{
	// Correct
	{
		auto expOut = std::vector<uint8_t>(
		{
			0xC1U,
				0x01U,
		});

		auto actOut = CatNullWriter::Write();
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatNull, Consistency)
{
	{
		auto inputAdvRlp = std::vector<uint8_t>(
		{
			0xC1U,
				0x01U,
		});
		auto decoded = CatNullParser().Parse(inputAdvRlp);
		auto encoded = CatNullWriter::Write();

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}
