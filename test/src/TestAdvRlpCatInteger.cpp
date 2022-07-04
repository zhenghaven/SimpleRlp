// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <AdvancedRlp/CatInteger.hpp>

#ifndef ADVANCEDRLP_CUSTOMIZED_NAMESPACE
using namespace AdvancedRlp;
#else
using namespace ADVANCEDRLP_CUSTOMIZED_NAMESPACE;
#endif

namespace SimpleRlp_Test
{
	extern size_t g_numOfTestFile;
}

GTEST_TEST(TestAdvRlpCatInteger, CountTestFile)
{
	static auto tmp = ++SimpleRlp_Test::g_numOfTestFile;
	(void)tmp;
}

template<
	typename _IntType,
	typename _Transform>
struct SpecTransformTestWrongType;

template<typename _Transform>
struct SpecTransformTestWrongType<int8_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<int8_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<uint8_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<uint8_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<int16_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<int16_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<uint16_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<uint16_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<int32_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, 0x00U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<int32_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<uint32_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, 0x00U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<uint32_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<int64_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, 0x00U, 0x00U,
									0x00U, 0x00U, 0x00U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<int64_t, _Transform>

template<typename _Transform>
struct SpecTransformTestWrongType<uint64_t, _Transform>
{
	void operator()()
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x00U, 0x00U, 0x00U,
									0x00U, 0x00U, 0x00U, 0x00U, }),
		};
		EXPECT_THROW(_Transform()(0, std::move(testList)), ParseError);
	}
}; // struct SpecTransformTestWrongType<uint64_t, _Transform>


GTEST_TEST(TestAdvRlpCatInteger, Transform_Int8)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<int8_t> >;

	// Correct parsing - positive
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int8(0x12));
	}

	// Correct parsing - negative
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x11U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int8(-1 * 0x12));
	}

	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x00U, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_UInt8)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<uint8_t> >;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::UInt8(0x12));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x00U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x00U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_Int16)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<int16_t> >;

	// Correct parsing - positive
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int16(0x3412));
	}

	// Correct parsing - negative
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x11U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int16(-1 * 0x3412));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x01U, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_UInt16)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<uint16_t> >;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::UInt16(0x3412));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x00U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x01U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_Int32)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<int32_t> >;

	// Correct parsing - positive
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int32(0x78563412));
	}

	// Correct parsing - negative
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x11U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int32(-1 * 0x78563412));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU, 0xFFU, 0xFFU, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x02U, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_UInt32)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<uint32_t> >;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::UInt32(0x78563412));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU, 0xFFU, 0xFFU, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x00U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x02U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_Int64)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<int64_t> >;

	// Correct parsing - positive
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int64(0x7856341278563412LL));
	}

	// Correct parsing - negative
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x11U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::Int64(-1 * 0x7856341278563412LL));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<uint64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU, 0xFFU, 0xFFU,
				0xFFU, 0xFFU, 0xFFU, 0xFFU, }),
		};

		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x03U, 0x10U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_UInt64)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			SpecificIntConverter<uint64_t> >;

	// Correct parsing
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U, }),
		};

		auto output = TF()(0, std::move(testList));
		EXPECT_EQ(
			output,
			SimpleObjects::UInt64(0x7856341278563412ULL));
	}

	SpecTransformTestWrongType<int8_t, TF>()();
	SpecTransformTestWrongType<uint8_t, TF>()();
	SpecTransformTestWrongType<int16_t, TF>()();
	SpecTransformTestWrongType<uint16_t, TF>()();
	SpecTransformTestWrongType<int32_t, TF>()();
	SpecTransformTestWrongType<uint32_t, TF>()();
	SpecTransformTestWrongType<int64_t, TF>()();

	// In correct raw data size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, }),
		};
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct integer value exceeds range
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0xFFU, 0xFFU, 0xFFU, 0xFFU,
				0xFFU, 0xFFU, 0xFFU, 0xFFU, }),
		};
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	auto zeroRawData = SimpleObjects::Bytes({ 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, });

	// In correct width byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0xFFU, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct signedness byte
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0xFFU, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct num of items in list
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x00U, }), zeroRawData,
			SimpleObjects::Bytes({ 0x00U, }), };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct specs size
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}

	// In correct cat ID
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x00U, 0x03U, 0x00U, }), zeroRawData, };
		EXPECT_THROW(TF()(0, std::move(testList)), ParseError);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Transform_Generic)
{
	using TF =
		TransformCatInteger<
			SimpleObjects::List,
			GenericIntConverter>;

	// int8_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::Int8);
				EXPECT_EQ(obj.AsCppInt8(), 0x12U);
			}
		);
	}

	// uint8_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x00U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::UInt8);
				EXPECT_EQ(obj.AsCppUInt8(), 0x12U);
			}
		);
	}

	// int16_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::Int16);
				EXPECT_EQ(obj.AsCppInt32(), 0x3412U);
			}
		);
	}

	// uint16_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x01U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::UInt16);
				EXPECT_EQ(obj.AsCppUInt32(), 0x3412U);
			}
		);
	}

	// int32_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::Int32);
				EXPECT_EQ(obj.AsCppInt32(), 0x78563412U);
			}
		);
	}

	// uint32_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x02U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::UInt32);
				EXPECT_EQ(obj.AsCppUInt32(), 0x78563412U);
			}
		);
	}

	// int64_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x10U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::Int64);
				EXPECT_EQ(obj.AsCppInt64(), 0x7856341278563412LL);
			}
		);
	}

	// uint64_t
	{
		SimpleObjects::List testList = {
			SimpleObjects::Bytes({ 0x04U, 0x03U, 0x00U, }),
			SimpleObjects::Bytes({ 0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U, }),
		};
		EXPECT_NO_THROW(
			{
				auto obj = TF()(0, std::move(testList));
				EXPECT_EQ(
					obj.AsRealNum().GetNumType(),
					SimpleObjects::RealNumType::UInt64);
				EXPECT_EQ(obj.AsCppUInt64(), 0x7856341278563412ULL);
			}
		);
	}

	// non-integer
	{
		EXPECT_THROW(
			GenericIntConverter().Convert(0, 0.0);,
			ParseError
		);
	}
}

GTEST_TEST(TestAdvRlpCatInteger, Parser)
{
	// Correct
	{
		auto output = CatIntegerParser().Parse(
			std::vector<uint8_t>(
				{
					0xC9U,
						0x83U,
							0x04U, 0x02U, 0x00U,
						0x84U,
							0x12U, 0x34U, 0x56U, 0x78U,
				}));

		auto expOut = SimpleObjects::Object(SimpleObjects::UInt32(0x78563412U));

		EXPECT_EQ(output, expOut);
		EXPECT_EQ(
			output.AsRealNum().GetNumType(),
			expOut.AsRealNum().GetNumType());
	}

	// Incorrect encoding - extra raw data
	{
		auto testProg = [](){
			CatIntegerParser().Parse(
				std::vector<uint8_t>({
					0xCAU,
						0x83U,
							0x04U, 0x02U, 0x00U,
						0x84U,
							0x12U, 0x34U, 0x56U, 0x78U,
						0x00U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - raw data is a list
	{
		auto testProg = [](){
			CatIntegerParser().Parse(
				std::vector<uint8_t>({
					0xCAU,
						0x83U,
							0x04U, 0x02U, 0x00U,
						0xC5U,
							0x84U,
								0x12U, 0x34U, 0x56U, 0x78U,
				}));
		};
		EXPECT_THROW(testProg(), ParseError);
	}

	// Incorrect encoding - extra raw data is a long byte
	{
		auto testProg = [](){
			CatIntegerParser().Parse(
				std::vector<uint8_t>({
					0xF8U, 0x42U,
						0x83U,
							0x04U, 0x02U, 0x00U,
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

template<typename _InValType>
static void TestWriter(
	const _InValType& input,
	const std::vector<uint8_t>& expOut)
{
	auto actOut = CatIntegerWriter::Write(input);
	EXPECT_EQ(expOut, actOut);
}

GTEST_TEST(TestAdvRlpCatInteger, Writer)
{
	// Correct; int8_t; positive
	TestWriter(
		SimpleObjects::Int8(0x12),
		std::vector<uint8_t>({
			0xC5U,
				0x83U,
					0x04U, 0x00U, 0x10U,
				0x12U,
	}));
	// Correct; int8_t; negative
	TestWriter(
		SimpleObjects::Int8(-1) * SimpleObjects::Int8(0x12),
		std::vector<uint8_t>({
			0xC5U,
				0x83U,
					0x04U, 0x00U, 0x11U,
				0x12U,
	}));
	// Correct; uint8_t;
	TestWriter(
		SimpleObjects::UInt8(0x12U),
		std::vector<uint8_t>({
			0xC5U,
				0x83U,
					0x04U, 0x00U, 0x00U,
				0x12U,
	}));

	// Correct; int16_t; positive
	TestWriter(
		SimpleObjects::Int16(0x3412),
		std::vector<uint8_t>({
			0xC7U,
				0x83U,
					0x04U, 0x01U, 0x10U,
				0x82U,
					0x12U, 0x34U,
	}));
	// Correct; int16_t; negative
	TestWriter(
		SimpleObjects::Int16(-1) * SimpleObjects::Int16(0x3412),
		std::vector<uint8_t>({
			0xC7U,
				0x83U,
					0x04U, 0x01U, 0x11U,
				0x82U,
					0x12U, 0x34U,
	}));
	// Correct; uint16_t;
	TestWriter(
		SimpleObjects::UInt16(0x3412U),
		std::vector<uint8_t>({
			0xC7U,
				0x83U,
					0x04U, 0x01U, 0x00U,
				0x82U,
					0x12U, 0x34U,
	}));

	// Correct; int32_t; positive
	TestWriter(
		SimpleObjects::Int32(0x78563412),
		std::vector<uint8_t>({
			0xC9U,
				0x83U,
					0x04U, 0x02U, 0x10U,
				0x84U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; int32_t; negative
	TestWriter(
		SimpleObjects::Int32(-1) * SimpleObjects::Int32(0x78563412),
		std::vector<uint8_t>({
			0xC9U,
				0x83U,
					0x04U, 0x02U, 0x11U,
				0x84U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; uint32_t;
	TestWriter(
		SimpleObjects::UInt32(0x78563412U),
		std::vector<uint8_t>({
			0xC9U,
				0x83U,
					0x04U, 0x02U, 0x00U,
				0x84U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));

	// Correct; int64_t; positive
	TestWriter(
		SimpleObjects::Int64(0x7856341278563412LL),
		std::vector<uint8_t>({
			0xCDU,
				0x83U,
					0x04U, 0x03U, 0x10U,
				0x88U,
					0x12U, 0x34U, 0x56U, 0x78U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; int64_t; negative
	TestWriter(
		SimpleObjects::Int64(-1) *
			SimpleObjects::Int64(0x7856341278563412LL),
		std::vector<uint8_t>({
			0xCDU,
				0x83U,
					0x04U, 0x03U, 0x11U,
				0x88U,
					0x12U, 0x34U, 0x56U, 0x78U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; uint64_t;
	TestWriter(
		SimpleObjects::UInt64(0x7856341278563412ULL),
		std::vector<uint8_t>({
			0xCDU,
				0x83U,
					0x04U, 0x03U, 0x00U,
				0x88U,
					0x12U, 0x34U, 0x56U, 0x78U,
					0x12U, 0x34U, 0x56U, 0x78U,
	}));

	// Incorrect; float
	{
		auto input = SimpleObjects::Float(0.0);
		EXPECT_THROW(CatIntegerWriter::Write(input), SerializeError);
	}
}

static void TestConsistency(const std::vector<uint8_t>& inputAdvRlp)
{
	auto decoded = CatIntegerParser().Parse(inputAdvRlp);
	auto encoded = CatIntegerWriter::Write(decoded.AsRealNum());

	EXPECT_EQ(encoded, inputAdvRlp);
}

GTEST_TEST(TestAdvRlpCatInteger, Consistency)
{
	// Correct; int8_t; positive
	TestConsistency(std::vector<uint8_t>({
		0xC5U,
			0x83U,
				0x04U, 0x00U, 0x10U,
			0x12U,
	}));
	// Correct; int8_t; negative
	TestConsistency(std::vector<uint8_t>({
		0xC5U,
			0x83U,
				0x04U, 0x00U, 0x11U,
			0x12U,
	}));
	// Correct; uint8_t;
	TestConsistency(std::vector<uint8_t>({
		0xC5U,
			0x83U,
				0x04U, 0x00U, 0x00U,
			0x12U,
	}));

	// Correct; int16_t; positive
	TestConsistency(std::vector<uint8_t>({
		0xC7U,
			0x83U,
				0x04U, 0x01U, 0x10U,
			0x82U,
				0x12U, 0x34U,
	}));
	// Correct; int16_t; negative
	TestConsistency(std::vector<uint8_t>({
		0xC7U,
			0x83U,
				0x04U, 0x01U, 0x11U,
			0x82U,
				0x12U, 0x34U,
	}));
	// Correct; uint16_t;
	TestConsistency(std::vector<uint8_t>({
		0xC7U,
			0x83U,
				0x04U, 0x01U, 0x00U,
			0x82U,
				0x12U, 0x34U,
	}));

	// Correct; int32_t; positive
	TestConsistency(std::vector<uint8_t>({
		0xC9U,
			0x83U,
				0x04U, 0x02U, 0x10U,
			0x84U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; int32_t; negative
	TestConsistency(std::vector<uint8_t>({
		0xC9U,
			0x83U,
				0x04U, 0x02U, 0x11U,
			0x84U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; uint32_t;
	TestConsistency(std::vector<uint8_t>({
		0xC9U,
			0x83U,
				0x04U, 0x02U, 0x00U,
			0x84U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));

	// Correct; int64_t; positive
	TestConsistency(std::vector<uint8_t>({
		0xCDU,
			0x83U,
				0x04U, 0x03U, 0x10U,
			0x88U,
				0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; int64_t; negative
	TestConsistency(std::vector<uint8_t>({
		0xCDU,
			0x83U,
				0x04U, 0x03U, 0x11U,
			0x88U,
				0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));
	// Correct; uint64_t;
	TestConsistency(std::vector<uint8_t>({
		0xCDU,
			0x83U,
				0x04U, 0x03U, 0x00U,
			0x88U,
				0x12U, 0x34U, 0x56U, 0x78U,
				0x12U, 0x34U, 0x56U, 0x78U,
	}));
}
