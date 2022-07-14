// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatString.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatString, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestAdvRlpCatString, Transform)
{
	using TF = TransformCatString;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x08U, 0x00U, }),
			SimpleObjects::Bytes({
				0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U,
				0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U, 0xE2U, 0x9CU, 0x85U, }),
		};
		SimpleObjects::String expOut =
			"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 \xE2\x9C\x85";

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(output, expOut);
	}

	// Incorrect num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x08U, 0x00U, }),
			SimpleObjects::Bytes({ 0x20U, }),
			SimpleObjects::Bytes({ 0x20U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect raw data is in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x08U, 0x00U, }),
			SimpleObjects::List({
				SimpleObjects::Bytes({ 0x20U, })}),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x08U, 0x00U,
				0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x20U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// Incorrect cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x20U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatString, Parser)
{

	// Correct
	{
		auto output = CatStringParser().Parse(
			std::vector<uint8_t>(
				{
					0xD1U,
						0x82U,
							0x08U, 0x00U,
						0x8DU,
							0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U,
							0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U, 0xE2U, 0x9CU, 0x85U,
				}));
		auto expOut =
			SimpleObjects::String("\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 \xE2\x9C\x85");

		EXPECT_EQ(output, expOut);
	}

	// Correct encoding - extra raw data is a long byte
	{
		auto output = CatStringParser().Parse(
			std::vector<uint8_t>({
				0xF8U, 0x41U,
					0x82U,
						0x08U, 0x00U,
					0xB8U, 0x3CU,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
						0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
			}));
		auto expOut =
			SimpleObjects::String(
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
				"\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 "
			);

		EXPECT_EQ(output, expOut);
	}

	// Incorrect encoding - unknown char width byte
	{
		auto testProg = [](){
			CatStringParser().Parse(
				std::vector<uint8_t>({
					0xD1U,
						0x82U,
							0x08U, 0xFFU,
						0x8DU,
							0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U,
							0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U, 0xE2U, 0x9CU, 0x85U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - no raw data
	{
		auto testProg = [](){
			CatStringParser().Parse(
				std::vector<uint8_t>({
					0xC3U,
						0x82U,
							0x08U, 0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a list
	{
		auto testProg = [](){
			CatStringParser().Parse(
				std::vector<uint8_t>({
					0xC5U,
						0x82U,
							0x08U, 0x00U,
						0xC1U,
							0x20U,
				}));
		};
		EXPECT_THROW(testProg(), SimpleRlp::ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatString, Writer)
{
	// Correct
	{
		auto input =
			SimpleObjects::String("\xF0\x9F\x98\x82 \xF0\x9F\x98\x86 \xE2\x9C\x85");
		auto expOut = std::vector<uint8_t>(
		{
			0xD1U,
				0x82U,
					0x08U, 0x00U,
				0x8DU,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U, 0xE2U, 0x9CU, 0x85U,
		});

		auto actOut = CatStringWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatString, Consistency)
{
	{
		auto inputAdvRlp = std::vector<uint8_t>(
		{
			0xD1U,
				0x82U,
					0x08U, 0x00U,
				0x8DU,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U, 0xE2U, 0x9CU, 0x85U,
		});
		auto decoded = CatStringParser().Parse(inputAdvRlp);
		auto encoded = CatStringWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
	{
		auto inputAdvRlp = std::vector<uint8_t>(
		{
			0xF8U, 0x41U,
				0x82U,
					0x08U, 0x00U,
				0xB8U, 0x3CU,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
					0xF0U, 0x9FU, 0x98U, 0x82U, 0x20U, 0xF0U, 0x9FU, 0x98U, 0x86U, 0x20U,
		});
		auto decoded = CatStringParser().Parse(inputAdvRlp);
		auto encoded = CatStringWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}
