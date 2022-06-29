// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatBytes.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatBytes, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}


GTEST_TEST(TestAdvRlpCatBytes, Transform)
{
	using TF =
		TransformCatBytes<SimpleObjects::List, SimpleRlp::GeneralParser>;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Bytes({ 0x00U, }));
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
			SimpleObjects::Bytes({ 0x00U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// In correct raw data type
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, }),
			SimpleObjects::String("test string"),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x01U, }),
			SimpleObjects::Bytes({ 0x00U, }),
		};

		EXPECT_THROW(
			TF()(0, std::move(testList)),
			ParseError);
	}
}


GTEST_TEST(TestAdvRlpCatBytes, Parser)
{

	// Correct; short bytes
	{
		auto output = CatBytesParser().Parse(
			std::vector<uint8_t>(
				{
					0xC9U,
						0x00U,
						0x87U,
							0x86U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
				}));

		auto expOut =
			SimpleObjects::Bytes({
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
			});

		EXPECT_EQ(output, expOut);
	}

	// Correct; long bytes
	{
		auto output = CatBytesParser().Parse(
			std::vector<uint8_t>(
				{
					0xF8U, 0x41U,
						0x00U,
						0xB8U, 0x3EU,
							0xB8U, 0x3CU,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
								0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				}));

		auto expOut =
			SimpleObjects::Bytes({
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
				0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			});

		EXPECT_EQ(output, expOut);
	}

	// Incorrect - "bytes" actually contains nested lists
	{
		auto testProg = [](){
			CatBytesParser().Parse(
				std::vector<uint8_t>(
					{
						0xD1U,
							0x00U,
							0x8FU,
								0xCEU,
									0x86U,
										0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
									0xC6U,
										0x83U,
											0x12U, 0x34U, 0x56U,
										0xC1U,
											0x05U,
					}));
		};

		EXPECT_THROW(testProg(), SimpleRlp::ParseError);
	}

	// Incorrect encoding - the raw data is a list
	{
		auto testProg = [](){
			CatBytesParser().Parse(
				std::vector<uint8_t>({
					0xC3U,
						0x00U,
						0xC1U,
							0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatBytes, Writer)
{
	// Correct - short bytes
	{
		auto input = SimpleObjects::Bytes({
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
		});
		auto expOut = std::vector<uint8_t>(
		{
			0xC9U,
				0x00U,
				0x87U,
					0x86U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
		});

		auto actOut = CatBytesWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}

	// Correct - Long bytes
	{
		auto input = SimpleObjects::Bytes({
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
			0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
		});
		auto expOut = std::vector<uint8_t>(
		{
			0xF8U, 0x41U,
				0x00U,
				0xB8U, 0x3EU,
					0xB8U, 0x3CU,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U,
		});

		auto actOut = CatBytesWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}
