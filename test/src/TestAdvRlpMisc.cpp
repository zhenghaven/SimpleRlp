// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatId.hpp>
#include <AdvancedRlp/WriterUtils.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpMisc, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestAdvRlpMisc, GetCatIdFromByte)
{
	EXPECT_EQ(GetCatIdFromByte(0x00U), CatId::Bytes);
	EXPECT_EQ(GetCatIdFromByte(0x01U), CatId::Null);
	EXPECT_EQ(GetCatIdFromByte(0x02U), CatId::False);
	EXPECT_EQ(GetCatIdFromByte(0x03U), CatId::True);
	EXPECT_EQ(GetCatIdFromByte(0x04U), CatId::Integer);
	EXPECT_EQ(GetCatIdFromByte(0x05U), CatId::Float);
	EXPECT_EQ(GetCatIdFromByte(0x08U), CatId::String);

	EXPECT_EQ(GetCatIdFromByte(0x20U), CatId::Array);
	EXPECT_EQ(GetCatIdFromByte(0x22U), CatId::Dict);
	EXPECT_EQ(GetCatIdFromByte(0x23U), CatId::StaticDict);

	EXPECT_THROW(GetCatIdFromByte(0xFFU), UnknownCatId);
}

GTEST_TEST(TestAdvRlpMisc, SerializeCatId)
{
	EXPECT_EQ(0x00U, SerializeCatId(CatId::Bytes));
	EXPECT_EQ(0x01U, SerializeCatId(CatId::Null));
	EXPECT_EQ(0x02U, SerializeCatId(CatId::False));
	EXPECT_EQ(0x03U, SerializeCatId(CatId::True));
	EXPECT_EQ(0x04U, SerializeCatId(CatId::Integer));
	EXPECT_EQ(0x05U, SerializeCatId(CatId::Float));
	EXPECT_EQ(0x08U, SerializeCatId(CatId::String));

	EXPECT_EQ(0x20U, SerializeCatId(CatId::Array));
	EXPECT_EQ(0x22U, SerializeCatId(CatId::Dict));
	EXPECT_EQ(0x23U, SerializeCatId(CatId::StaticDict));
}

GTEST_TEST(TestAdvRlpMisc, UnknownCatId)
{
	auto exp = UnknownCatId(0xFFU);
	EXPECT_EQ(exp.what(), std::string("Unkown CAT ID - \\xFF"));
}

GTEST_TEST(TestAdvRlpMisc, PrimitiveToRaw)
{
	// size ok
	{
		std::vector<uint8_t> ctn;
		uint32_t testVal = 0x12345678U;
		ctn.resize(sizeof(testVal));

		Internal::PrimitiveToRaw<Internal::SimRlp::Internal::Endian::little>::
			FromInt(ctn.data(), ctn.size(), testVal);

		EXPECT_EQ(ctn, std::vector<uint8_t>({ 0x78U, 0x56U, 0x34U, 0x12U, }));
	}

	// size not matching
	{
		std::vector<uint8_t> ctn;
		uint32_t testVal = 0x12345678U;
		ctn.resize(sizeof(testVal) + 1);

		auto testProg = [&]() {
			Internal::PrimitiveToRaw<Internal::SimRlp::Internal::Endian::little>::
				FromInt(ctn.data(), ctn.size(), testVal);
		};
		EXPECT_THROW(testProg(), SerializeError);
	}
}
