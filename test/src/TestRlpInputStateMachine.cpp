// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleRlp/InputStateMachine.hpp>

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
using namespace SimpleRlp;
#else
using namespace SIMPLERLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestRlpInputStateMachine, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestRlpInputStateMachine, DecodeRlpLeadingByte)
{
	// single Byte
	EXPECT_NO_THROW(
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::Byte, 0x0000U),
			DecodeRlpLeadingByte<uint32_t>(0x0000U, 0)
		);
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::Byte, 0x007FU),
			DecodeRlpLeadingByte<uint32_t>(0x007FU, 0)
		);
	);

	// bytes short
	EXPECT_NO_THROW(
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::BytesShort, 0x0000U),
			DecodeRlpLeadingByte<uint32_t>(0x0080U, 0)
		);
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::BytesShort, 0x0037U),
			DecodeRlpLeadingByte<uint32_t>(0x00B7U, 0)
		);
	);

	// bytes long
	EXPECT_NO_THROW(
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::BytesLong, 0x0001U),
			DecodeRlpLeadingByte<uint32_t>(0x00B8U, 0)
		);
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::BytesLong, 0x0008U),
			DecodeRlpLeadingByte<uint32_t>(0x00BFU, 0)
		);
	);

	// list short
	EXPECT_NO_THROW(
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::ListShort, 0x0000U),
			DecodeRlpLeadingByte<uint32_t>(0x00C0U, 0)
		);
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::ListShort, 0x0037U),
			DecodeRlpLeadingByte<uint32_t>(0x00F7U, 0)
		);
	);

	// list long
	EXPECT_NO_THROW(
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::ListLong, 0x0001U),
			DecodeRlpLeadingByte<uint32_t>(0x00F8U, 0)
		);
		EXPECT_EQ(
			std::make_pair(RlpEncodeType::ListLong, 0x0008U),
			DecodeRlpLeadingByte<uint32_t>(0x00FFU, 0)
		);
	);

	// larger than a byte
	EXPECT_THROW(
		DecodeRlpLeadingByte<uint32_t>(0x0100U, 0);,
		ParseError
	);
}

GTEST_TEST(TestRlpInputStateMachine, ParseSizeValue)
{
	size_t i = 0;
	auto testInFunc = [&]()
	{
		return static_cast<uint32_t>(i++);
	};

	// little endian
	using LittleType = Internal::ParseSizeValue<Internal::Endian::little>;

	// input: 0x00 0x01 0x02 0x03 0x04
	// little endian bytes: 0x04 0x03 0x02 0x01 0x00 | 0x00 0x00 0x00
	// expected: 0x0001020304
	i = 0x00U;
	EXPECT_NO_THROW(
		EXPECT_EQ(
			LittleType::Parse(5, 0, testInFunc),
			0x0001020304ULL
		);
	);

	// input: 0xFF
	// little endian bytes: 0xFF | 0x00 0x00 0x00 0x00 0x00 0x00 0x00
	// expected: 0x00FF
	i = 0x00FFU;
	EXPECT_NO_THROW(
		EXPECT_EQ(
			LittleType::Parse(1, 0, testInFunc),
			0x00FFULL
		);
	);

	// Exceeds 1 byte value range
	i = 0x00FFU;
	EXPECT_THROW(
		LittleType::Parse(2, 0, testInFunc);,
		ParseError
	);
}

namespace
{

template<typename _ForwardItType>
class TestForwardIteratorStateMachine :
	public ForwardIteratorStateMachine<_ForwardItType>
{
public:

	using Base = ForwardIteratorStateMachine<_ForwardItType>;
	using Self = TestForwardIteratorStateMachine<_ForwardItType>;

	using value_type =
		typename std::iterator_traits<_ForwardItType>::value_type;

	using Base::ForwardIteratorStateMachine;

	std::pair<bool, value_type> TestInternalNextVal()
	{
		return Base::InternalNextVal();
	}

}; // class TestForwardIteratorStateMachine

}

GTEST_TEST(TestRlpInputStateMachine, ForwardIterator)
{
	using TestValueType = uint8_t;
	using IteratorType    = Internal::Obj::FrIterator<TestValueType, true>;
	using ISMType         = TestForwardIteratorStateMachine<IteratorType>;

	std::vector<TestValueType> testInput = { 0x12U };
	ISMType ism(
		Internal::Obj::ToFrIt<true>(testInput.cbegin()),
		Internal::Obj::ToFrIt<true>(testInput.cend()));

	EXPECT_EQ(ism.GetBytesCount(), 0);
	EXPECT_EQ(ism.GetByte(), 0x12U);
	EXPECT_EQ(ism.GetByteAndAdv(), 0x12U);

	EXPECT_EQ(ism.GetBytesCount(), 1);
	EXPECT_THROW(ism.GetByte(), ParseError);
	EXPECT_THROW(ism.GetByteAndAdv(), ParseError);
	EXPECT_EQ(
		ism.TestInternalNextVal(),
		std::make_pair(true, TestValueType()));
}
