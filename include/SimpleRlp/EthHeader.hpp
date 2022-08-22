// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "Internal/SimpleObjects.hpp"

#ifndef SIMPLERLP_CUSTOMIZED_NAMESPACE
namespace SimpleRlp
#else
namespace SIMPLERLP_CUSTOMIZED_NAMESPACE
#endif
{

namespace Internal
{
// Names are from: https://github.com/ethereum/go-ethereum/blob/master/core/types/block.go
template<typename _BytesObjType>
using EthHeaderTupleCore = std::tuple<
	// 01.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ParentHash")>,
		_BytesObjType>,
	// 02.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")>,
		_BytesObjType>,
	// 03.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Miner")>,
		_BytesObjType>,
	// 04.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("StateRoot")>,
		_BytesObjType>,
	// 05.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")>,
		_BytesObjType>,
	// 06.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")>,
		_BytesObjType>,
	// 07.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("LogsBloom")>,
		_BytesObjType>,
	// 08.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Difficulty")>,
		_BytesObjType>,
	// 09.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Number")>,
		_BytesObjType>,
	// 10.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("GasLimit")>,
		_BytesObjType>,
	// 11.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("GasUsed")>,
		_BytesObjType>,
	// 12.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Timestamp")>,
		_BytesObjType>,
	// 13.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ExtraData")>,
		_BytesObjType>,
	// 14.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("MixHash")>,
		_BytesObjType>,
	// 15.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Nonce")>,
		_BytesObjType>,
	// 16.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("BaseFee")>,
		_BytesObjType>
	>;

template<typename _BytesParserType>
using EthHeaderParserTupleCore = std::tuple<
	// 01.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ParentHash")>,
		_BytesParserType>,
	// 02.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")>,
		_BytesParserType>,
	// 03.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Miner")>,
		_BytesParserType>,
	// 04.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("StateRoot")>,
		_BytesParserType>,
	// 05.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")>,
		_BytesParserType>,
	// 06.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")>,
		_BytesParserType>,
	// 07.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("LogsBloom")>,
		_BytesParserType>,
	// 08.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Difficulty")>,
		_BytesParserType>,
	// 09.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Number")>,
		_BytesParserType>,
	// 10.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("GasLimit")>,
		_BytesParserType>,
	// 11.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("GasUsed")>,
		_BytesParserType>,
	// 12.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Timestamp")>,
		_BytesParserType>,
	// 13.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("ExtraData")>,
		_BytesParserType>,
	// 14.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("MixHash")>,
		_BytesParserType>,
	// 15.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("Nonce")>,
		_BytesParserType>,
	// 16.
	std::pair<Obj::StrKey<SIMOBJ_KSTR("BaseFee")>,
		_BytesParserType>
	>;

} // namespace Internal


template<typename _BytesObjType>
class EthHeaderImpl :
	public Internal::Obj::StaticDict<
		Internal::EthHeaderTupleCore<_BytesObjType> >
{
public: // static members:

	using Self = EthHeaderImpl<_BytesObjType>;
	using Base = Internal::Obj::StaticDict<
		Internal::EthHeaderTupleCore<_BytesObjType> >;

public:

	using Base::Base;

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ParentHash")> >
	get_ParentHash()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ParentHash")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ParentHash")> >
	get_ParentHash() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ParentHash")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")> >
	get_Sha3Uncles()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")> >
	get_Sha3Uncles() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Sha3Uncles")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Miner")> >
	get_Miner()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Miner")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Miner")> >
	get_Miner() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Miner")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("StateRoot")> >
	get_StateRoot()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("StateRoot")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("StateRoot")> >
	get_StateRoot() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("StateRoot")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")> >
	get_TransactionsRoot()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")> >
	get_TransactionsRoot() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("TransactionsRoot")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")> >
	get_ReceiptsRoot()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")> >
	get_ReceiptsRoot() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ReceiptsRoot")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("LogsBloom")> >
	get_LogsBloom()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("LogsBloom")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("LogsBloom")> >
	get_LogsBloom() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("LogsBloom")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Difficulty")> >
	get_Difficulty()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Difficulty")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Difficulty")> >
	get_Difficulty() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Difficulty")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Number")> >
	get_Number()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Number")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Number")> >
	get_Number() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Number")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("GasLimit")> >
	get_GasLimit()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("GasLimit")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("GasLimit")> >
	get_GasLimit() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("GasLimit")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("GasUsed")> >
	get_GasUsed()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("GasUsed")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("GasUsed")> >
	get_GasUsed() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("GasUsed")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Timestamp")> >
	get_Timestamp()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Timestamp")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Timestamp")> >
	get_Timestamp() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Timestamp")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ExtraData")> >
	get_ExtraData()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ExtraData")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("ExtraData")> >
	get_ExtraData() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("ExtraData")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("MixHash")> >
	get_MixHash()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("MixHash")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("MixHash")> >
	get_MixHash() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("MixHash")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Nonce")> >
	get_Nonce()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Nonce")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("Nonce")> >
	get_Nonce() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("Nonce")> >();
	}

	typename Base::template GetRef<Internal::Obj::StrKey<SIMOBJ_KSTR("BaseFee")> >
	get_BaseFee()
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("BaseFee")> >();
	}

	typename Base::template GetConstRef<Internal::Obj::StrKey<SIMOBJ_KSTR("BaseFee")> >
	get_BaseFee() const
	{
		return Base::template get<Internal::Obj::StrKey<SIMOBJ_KSTR("BaseFee")> >();
	}

}; // class EthHeaderImpl

} // namespace SimpleRlp
