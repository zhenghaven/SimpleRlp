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

GTEST_TEST(TestRlpFailingParser, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestRlpFailingParser, Bytes_Parse)
{
	{
		std::vector<uint8_t> input = { 0x00U, };
		EXPECT_THROW(
			FailingParserBytes().Parse(input);,
			ParseError);
	}

	{
		using IteratorType    = SimpleObjects::FrIterator<uint8_t, true>;
		using ISMType         = ForwardIteratorStateMachine<IteratorType>;

		std::vector<uint8_t> input = { 0x00U, };
		ISMType ism(
			SimpleObjects::ToFrIt<true>(input.cbegin()),
			SimpleObjects::ToFrIt<true>(input.cend()));
		size_t byteLeft = 0;
		EXPECT_THROW(
			FailingParserBytes().Parse(ism, byteLeft);,
			ParseError);
	}

	{
		using IteratorType    = SimpleObjects::FrIterator<uint8_t, true>;
		using ISMType         = ForwardIteratorStateMachine<IteratorType>;

		std::vector<uint8_t> input = { 0x00U, };
		ISMType ism(
			SimpleObjects::ToFrIt<true>(input.cbegin()),
			SimpleObjects::ToFrIt<true>(input.cend()));
		size_t byteLeft = 0;
		EXPECT_THROW(
			FailingParserBytes().Parse(ism, RlpEncodeType::Byte, 0, byteLeft);,
			ParseError);
	}
}

GTEST_TEST(TestRlpFailingParser, List_Parse)
{
	{
		std::vector<uint8_t> input = { 0xC0U, };
		EXPECT_THROW(
			FailingParserList().Parse(input);,
			ParseError);
	}

	{
		using IteratorType    = SimpleObjects::FrIterator<uint8_t, true>;
		using ISMType         = ForwardIteratorStateMachine<IteratorType>;

		std::vector<uint8_t> input = { 0xC0U, };
		ISMType ism(
			SimpleObjects::ToFrIt<true>(input.cbegin()),
			SimpleObjects::ToFrIt<true>(input.cend()));
		size_t byteLeft = 0;
		EXPECT_THROW(
			FailingParserList().Parse(ism, byteLeft);,
			ParseError);
	}

	{
		using IteratorType    = SimpleObjects::FrIterator<uint8_t, true>;
		using ISMType         = ForwardIteratorStateMachine<IteratorType>;

		std::vector<uint8_t> input = { 0xC0U, };
		ISMType ism(
			SimpleObjects::ToFrIt<true>(input.cbegin()),
			SimpleObjects::ToFrIt<true>(input.cend()));
		size_t byteLeft = 0;
		EXPECT_THROW(
			FailingParserList().Parse(
				ism, RlpEncodeType::ListShort, 0, byteLeft);,
			ParseError);
	}
}
