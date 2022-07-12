// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatBoolean.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatBoolean, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestAdvRlpCatBoolean, TransformFalse)
{
	using TF = TransformCatFalse;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x02U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Bool(false));
	}

	// Incorrect num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x02U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x02U, 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatBoolean, TransformTrue)
{
	using TF = TransformCatTrue;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x03U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Bool(true));
	}

	// Incorrect num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x03U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x03U, 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatBoolean, ParserFalse)
{
	// Correct
	{
		auto output = CatFalseParser().Parse(
			std::vector<uint8_t>(
				{
					0xC1U,
						0x02U,
				}));

		auto expOut = SimpleObjects::Bool(false);

		EXPECT_EQ(output, expOut);
	}

	// Incorrect encoding - extra raw data
	{
		auto testProg = [](){
			CatFalseParser().Parse(
				std::vector<uint8_t>({
					0xC2U,
						0x02U,
						0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a list
	{
		auto testProg = [](){
			CatFalseParser().Parse(
				std::vector<uint8_t>({
					0xC3U,
						0x02U,
						0xC1U,
							0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a long byte
	{
		auto testProg = [](){
			CatFalseParser().Parse(
				std::vector<uint8_t>({
					0xF8U, 0x3FU,
						0x02U,
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

GTEST_TEST(TestAdvRlpCatBoolean, ParserTrue)
{
	// Correct
	{
		auto output = CatTrueParser().Parse(
			std::vector<uint8_t>(
				{
					0xC1U,
						0x03U,
				}));

		auto expOut = SimpleObjects::Bool(true);

		EXPECT_EQ(output, expOut);
	}

	// Incorrect encoding - extra raw data
	{
		auto testProg = [](){
			CatTrueParser().Parse(
				std::vector<uint8_t>({
					0xC2U,
						0x03U,
						0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a list
	{
		auto testProg = [](){
			CatTrueParser().Parse(
				std::vector<uint8_t>({
					0xC3U,
						0x03U,
						0xC1U,
							0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a long byte
	{
		auto testProg = [](){
			CatTrueParser().Parse(
				std::vector<uint8_t>({
					0xF8U, 0x3FU,
						0x03U,
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

GTEST_TEST(TestAdvRlpCatBoolean, Writer)
{
	// Correct; false
	{
		auto input = SimpleObjects::Bool(false);
		auto expOut = std::vector<uint8_t>(
		{
			0xC1U,
				0x02U,
		});

		auto actOut = CatBooleanWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
	// Correct; true
	{
		auto input = SimpleObjects::Bool(true);
		auto expOut = std::vector<uint8_t>(
		{
			0xC1U,
				0x03U,
		});

		auto actOut = CatBooleanWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatBoolean, Consistency)
{
	// false
	{
		auto inputAdvRlp = std::vector<uint8_t>(
		{
			0xC1U,
				0x02U,
		});
		auto decoded = CatFalseParser().Parse(inputAdvRlp);
		auto encoded = CatBooleanWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}

	// true
	{
		auto inputAdvRlp = std::vector<uint8_t>(
		{
			0xC1U,
				0x03U,
		});
		auto decoded = CatTrueParser().Parse(inputAdvRlp);
		auto encoded = CatBooleanWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}
