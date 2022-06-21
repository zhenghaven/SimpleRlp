// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <SimpleObjects/StaticDict.hpp>
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

GTEST_TEST(TestStaticDictParser, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

namespace
{

using TestStaticDict1Tp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")>,
		SimpleObjects::Bytes>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")>,
		SimpleObjects::Bytes>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")>,
		SimpleObjects::Bytes>
	>;

class TestStaticDict1 :
	public SimpleObjects::StaticDict<
		TestStaticDict1Tp>
{
public: // static members:

	using Self = TestStaticDict1;
	using Base = SimpleObjects::StaticDict<
		TestStaticDict1Tp>;

public:

	using Base::StaticDictImpl;

	SimpleObjects::Bytes& get_Key1_1()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

	const SimpleObjects::Bytes& get_Key1_1() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

	SimpleObjects::Bytes& get_Key1_2()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")> >();
	}

	const SimpleObjects::Bytes& get_Key1_2() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")> >();
	}

	SimpleObjects::Bytes& get_Key1_3()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")> >();
	}

	const SimpleObjects::Bytes& get_Key1_3() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")> >();
	}

}; // class TestStaticDict1

using TestStaticDict1ParserTp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")>,
		BytesParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")>,
		BytesParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")>,
		BytesParser>
	>;

using TestStaticDict1Parser = StaticDictParserT<
	TestStaticDict1ParserTp,
	false,
	false,
	TestStaticDict1>;

using TestStaticDict2Tp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")>,
		SimpleObjects::Bytes>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_2")>,
		TestStaticDict1>
	>;

class TestStaticDict2 :
	public SimpleObjects::StaticDict<
		TestStaticDict2Tp>
{
public: // static members:

	using Self = TestStaticDict2;
	using Base = SimpleObjects::StaticDict<
		TestStaticDict2Tp>;

public:

	using Base::StaticDictImpl;

	SimpleObjects::Bytes& get_Key2_1()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	const SimpleObjects::Bytes& get_Key2_1() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	TestStaticDict1& get_Key2_2()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_2")> >();
	}

	const TestStaticDict1& get_Key2_2() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_2")> >();
	}

}; // class TestStaticDict2

using TestStaticDict2ParserTp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")>,
		BytesParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_2")>,
		TestStaticDict1Parser>
	>;

using TestStaticDict2Parser = StaticDictParserT<
		TestStaticDict2ParserTp,
		false,
		false,
		TestStaticDict2>;

} // namespace


GTEST_TEST(TestStaticDictParser, TestStaticDict1_Short)
{
	// Short
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({ 0x78U, 0x90U, });
	expObj.get_Key1_3() = SimpleObjects::Bytes({ 0x09U, 0x87U, 0x65U, 0x43U, });

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xCCU,
			0x83U, 0x12U, 0x34U, 0x56U,
			0x82U, 0x78U, 0x90U,
			0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
	});
	auto actRlp = WriteRlp(expObj);
	EXPECT_EQ(actRlp, expRlp);

	auto actObj = TestStaticDict1Parser().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
	EXPECT_EQ(actObj.get_Key1_3(), expObj.get_Key1_3());
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1_Long)
{
	// Long
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({ 0x78U, 0x90U, });
	expObj.get_Key1_3() = SimpleObjects::Bytes({
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xF8U, 0x45U,
			0x83U, 0x12U, 0x34U, 0x56U,
			0x82U, 0x78U, 0x90U,
			0xB8U, 0x3CU,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});
	auto actRlp = WriteRlp(expObj);
	EXPECT_EQ(actRlp, expRlp);

	auto actObj = TestStaticDict1Parser().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
	EXPECT_EQ(actObj.get_Key1_3(), expObj.get_Key1_3());
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1Parser_Missing)
{
	// Missing item
	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
			0xC7U,
				0x83U, 0x12U, 0x34U, 0x56U,
				0x82U, 0x78U, 0x90U,
		});

	EXPECT_THROW(
		TestStaticDict1Parser().Parse(expRlp);,
		ParseError
	);
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1Parser_Extra)
{
	// Extra item
	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xD1U,
			0x83U, 0x12U, 0x34U, 0x56U,
			0x82U, 0x78U, 0x90U,
			0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
			0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
	});

	EXPECT_THROW(
		TestStaticDict1Parser().Parse(expRlp);,
		ParseError
	);
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1Parser_WrongType)
{
	// Extra item
	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
	});

	EXPECT_THROW(
		TestStaticDict1Parser().Parse(expRlp);,
		ParseError
	);
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1ParserTF_Short)
{
	// AllowMissingItem
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({ 0x78U, 0x90U, });

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
			0xC7U,
				0x83U, 0x12U, 0x34U, 0x56U,
				0x82U, 0x78U, 0x90U,
		});

	using TestStaticDict1ParserTF = StaticDictParserT<
		TestStaticDict1ParserTp,
		true,
		false,
		TestStaticDict1>;
	auto actObj = TestStaticDict1ParserTF().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1ParserTF_Long)
{
	// AllowMissingItem
	// Long
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xF8U, 0x42U,
			0x83U, 0x12U, 0x34U, 0x56U,
			0xB8U, 0x3CU,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});

	using TestStaticDict1ParserTF = StaticDictParserT<
		TestStaticDict1ParserTp,
		true,
		false,
		TestStaticDict1>;
	auto actObj = TestStaticDict1ParserTF().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
}


GTEST_TEST(TestStaticDictParser, TestStaticDict1ParserTT_Short)
{
	// AllowExtraItem
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({ 0x78U, 0x90U, });
	expObj.get_Key1_3() = SimpleObjects::Bytes({ 0x09U, 0x87U, 0x65U, 0x43U, });

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xD1U,
			0x83U, 0x12U, 0x34U, 0x56U,
			0x82U, 0x78U, 0x90U,
			0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
			0x84U, 0x65U, 0x43U, 0x09U, 0x87U,
	});

	using TestStaticDict1ParserTF = StaticDictParserT<
		TestStaticDict1ParserTp,
		true,
		true,
		TestStaticDict1>;
	auto actObj = TestStaticDict1ParserTF().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
	EXPECT_EQ(actObj.get_Key1_3(), expObj.get_Key1_3());

}


GTEST_TEST(TestStaticDictParser, TestStaticDict1ParserTT_Long)
{
	// AllowExtraItem
	TestStaticDict1 expObj;
	expObj.get_Key1_1() = SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key1_2() = SimpleObjects::Bytes({ 0x78U, 0x90U, });
	expObj.get_Key1_3() = SimpleObjects::Bytes({
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xF8U, 0x4AU,
				0x83U, 0x12U, 0x34U, 0x56U,
				0x82U, 0x78U, 0x90U,
				0xB8U, 0x3CU,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
					0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x84U, 0x65U, 0x43U, 0x09U, 0x87U,
	});

	using TestStaticDict1ParserTF = StaticDictParserT<
		TestStaticDict1ParserTp,
		true,
		true,
		TestStaticDict1>;
	auto actObj = TestStaticDict1ParserTF().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key1_1(), expObj.get_Key1_1());
	EXPECT_EQ(actObj.get_Key1_2(), expObj.get_Key1_2());
	EXPECT_EQ(actObj.get_Key1_3(), expObj.get_Key1_3());
}


GTEST_TEST(TestStaticDictParser, TestStaticDict2)
{
	TestStaticDict2 expObj;
	expObj.get_Key2_1() = SimpleObjects::Bytes({
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
		0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
	});
	expObj.get_Key2_2().get_Key1_1() =
		SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, });
	expObj.get_Key2_2().get_Key1_2() =
		SimpleObjects::Bytes({ 0x78U, 0x90U, });
	expObj.get_Key2_2().get_Key1_3() =
		SimpleObjects::Bytes({ 0x09U, 0x87U, 0x65U, 0x43U, });

	// Test RLP writer
	auto expRlp = std::vector<uint8_t>({
		0xF8U, 0x4BU,
			0xB8U, 0x3CU,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
				0x12U, 0x34U, 0x56U, 0x78U, 0x90U, 0x12U, 0x34U, 0x56U, 0x78U, 0x90U,
			0xCCU,
				0x83U, 0x12U, 0x34U, 0x56U,
				0x82U, 0x78U, 0x90U,
				0x84U, 0x09U, 0x87U, 0x65U, 0x43U,
	});
	auto actRlp = WriteRlp(expObj);
	EXPECT_EQ(actRlp, expRlp);

	auto actObj = TestStaticDict2Parser().Parse(expRlp);
	EXPECT_EQ(actObj.get_Key2_1(), expObj.get_Key2_1());
	EXPECT_EQ(
		actObj.get_Key2_2().get_Key1_1(),
		expObj.get_Key2_2().get_Key1_1());
	EXPECT_EQ(
		actObj.get_Key2_2().get_Key1_2(),
		expObj.get_Key2_2().get_Key1_2());
	EXPECT_EQ(
		actObj.get_Key2_2().get_Key1_3(),
		expObj.get_Key2_2().get_Key1_3());
}
