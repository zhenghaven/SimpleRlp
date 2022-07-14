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

GTEST_TEST(TestAdvRlpCatStaticDict, CountTestFile)
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
		SimpleObjects::Bool>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")>,
		SimpleObjects::String>
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

	using Base::Base;

	SimpleObjects::Bytes& get_Key1_1()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

	const SimpleObjects::Bytes& get_Key1_1() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")> >();
	}

	SimpleObjects::Bool& get_Key1_2()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")> >();
	}

	const SimpleObjects::Bool& get_Key1_2() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")> >();
	}

	SimpleObjects::String& get_Key1_3()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")> >();
	}

	const SimpleObjects::String& get_Key1_3() const
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")> >();
	}

}; // class TestStaticDict1

using TestStaticDict1ParserTp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_1")>,
		CatBytesParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_2")>,
		CatBooleanParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key1_3")>,
		CatStringParser >
	>;

using TestStaticDict1Parser = CatStaticDictParserT<
	TestStaticDict1ParserTp,
	false,
	false,
	TestStaticDict1>;





using TestStaticDict2Tp = std::tuple<
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")>,
		SimpleObjects::List>,
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

	using Base::Base;

	SimpleObjects::List& get_Key2_1()
	{
		return Base::get<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_1")> >();
	}

	const SimpleObjects::List& get_Key2_1() const
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
		CatArrayParser>,
	std::pair<SimpleObjects::StrKey<SIMOBJ_KSTR("Key2_2")>,
		TestStaticDict1Parser>
	>;

using TestStaticDict2Parser = CatStaticDictParserT<
		TestStaticDict2ParserTp,
		false,
		false,
		TestStaticDict2>;

} // namespace


static std::vector<uint8_t> GetExpectedAdvRlpSDict1()
{
	return std::vector<uint8_t>({
		0xD5U,
			0x23U,
			0xC8U, // [0] bytes
				0x00U,
				0x86U,
					0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
			0xC1U, // [1] true
				0x03U,
			0xC8U, // [2] string - "val1"
				0x82U,
					0x08U, 0x00U,
				0x84U,
					0x76U, 0x61U, 0x6CU, 0x31U,
	});
}

static TestStaticDict1 GetExpectedObjSDict1()
{
	TestStaticDict1 res;
	res.get_Key1_1() =
		SimpleObjects::Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, });
	res.get_Key1_2() = SimpleObjects::Bool(true);
	res.get_Key1_3() = SimpleObjects::String("val1");
	return res;
}

static std::vector<uint8_t> GetExpectedAdvRlpSDict2()
{
	return std::vector<uint8_t>({
		0xDFU,
			0x23U,
			0xC7U, // [0] Array
				0x20U,
				0xC5U,
					0x00U,
					0x83U,
						0x12U, 0x34U, 0x56U,
			0xD5U, // [1] TestStaticDict1
				0x23U,
				0xC8U, // [0] bytes
					0x00U,
					0x86U,
						0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U,
				0xC1U, // [1] true
					0x03U,
				0xC8U, // [2] string - "val1"
					0x82U,
						0x08U, 0x00U,
					0x84U,
						0x76U, 0x61U, 0x6CU, 0x31U,
	});
}

static TestStaticDict2 GetExpectedObjSDict2()
{
	TestStaticDict2 res;
	res.get_Key2_1() = SimpleObjects::List({
		SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, }),
	});

	res.get_Key2_2().get_Key1_1() =
		SimpleObjects::Bytes({ 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, });
	res.get_Key2_2().get_Key1_2() = SimpleObjects::Bool(true);
	res.get_Key2_2().get_Key1_3() = SimpleObjects::String("val1");
	return res;
}


GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict1Parser)
{
	// Correct
	{
		auto input = GetExpectedAdvRlpSDict1();
		auto expOut = GetExpectedObjSDict1();

		auto actOut = TestStaticDict1Parser().Parse(input);
		EXPECT_EQ(expOut.get_Key1_1(), actOut.get_Key1_1());
		EXPECT_EQ(expOut.get_Key1_2(), actOut.get_Key1_2());
		EXPECT_EQ(expOut.get_Key1_3(), actOut.get_Key1_3());
	}

	// Incorrect - extra specs bytes
	{
		std::vector<uint8_t> input = {
			0xC3U,
				0x82U,
					0x23U, 0x00U,
		};
		EXPECT_THROW(
			TestStaticDict1Parser().Parse(input);,
			ParseError);
	}

	// Incorrect - wrong CAT ID
	{
		std::vector<uint8_t> input = {
			0xC2U,
				0x81U,
					0x00U,
		};
		EXPECT_THROW(
			TestStaticDict1Parser().Parse(input);,
			ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict2Parser)
{
	// Correct
	{
		auto input = GetExpectedAdvRlpSDict2();
		auto expOut = GetExpectedObjSDict2();

		auto actOut = TestStaticDict2Parser().Parse(input);
		EXPECT_EQ(expOut.get_Key2_1(), actOut.get_Key2_1());
		EXPECT_EQ(expOut.get_Key2_2().get_Key1_1(),
			actOut.get_Key2_2().get_Key1_1());
		EXPECT_EQ(expOut.get_Key2_2().get_Key1_2(),
			actOut.get_Key2_2().get_Key1_2());
		EXPECT_EQ(expOut.get_Key2_2().get_Key1_3(),
			actOut.get_Key2_2().get_Key1_3());
	}

	// Incorrect - extra specs bytes
	{
		std::vector<uint8_t> input = {
			0xC3U,
				0x82U,
					0x23U, 0x00U,
		};
		EXPECT_THROW(
			TestStaticDict2Parser().Parse(input);,
			ParseError);
	}

	// Incorrect - wrong CAT ID
	{
		std::vector<uint8_t> input = {
			0xC2U,
				0x81U,
					0x00U,
		};
		EXPECT_THROW(
			TestStaticDict2Parser().Parse(input);,
			ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict1Writer)
{
	// Correct
	{
		auto input = GetExpectedObjSDict1();
		auto expOut = GetExpectedAdvRlpSDict1();

		auto actOut = GenericWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict2Writer)
{
	// Correct
	{
		auto input = GetExpectedObjSDict2();
		auto expOut = GetExpectedAdvRlpSDict2();

		auto actOut = GenericWriter::Write(input);
		EXPECT_EQ(expOut, actOut);
	}
}

GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict1Consistency)
{
	{
		auto inputAdvRlp = GetExpectedAdvRlpSDict1();
		auto decoded = TestStaticDict1Parser().Parse(inputAdvRlp);
		auto encoded = GenericWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}

GTEST_TEST(TestAdvRlpCatStaticDict, TestStaticDict2Consistency)
{
	{
		auto inputAdvRlp = GetExpectedAdvRlpSDict2();
		auto decoded = TestStaticDict2Parser().Parse(inputAdvRlp);
		auto encoded = GenericWriter::Write(decoded);

		EXPECT_EQ(encoded, inputAdvRlp);
	}
}
