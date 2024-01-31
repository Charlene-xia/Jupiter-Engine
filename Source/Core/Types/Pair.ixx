// Copyright Jupiter Technologies, Inc. All Rights Reserved.

export module jpt.Pair;

import jpt.Utilities;
import jpt.ToString;
import jpt.String;

export namespace jpt 
{
	template<typename TFirst, typename TSecond>
	struct Pair
	{
	public:
		TFirst first;
		TSecond second;

	public:
		constexpr Pair() = default;
		constexpr Pair(const TFirst& inFirst, const TSecond& inSecond);
		constexpr Pair(const TFirst& inFirst, TSecond&& inSecond);
		constexpr Pair(TFirst&& inFirst, const TSecond& inSecond);
		constexpr Pair(TFirst&& inFirst, TSecond&& inSecond);

		constexpr String ToString() const;
	};

	template<typename TFirst, typename TSecond>
	constexpr bool operator==(const Pair<TFirst, TSecond>& a, const Pair<TFirst, TSecond>& b)
	{
		return a.first == b.first && a.second == b.second;
	}

	template<typename TFirst, typename TSecond>
	constexpr Pair<TFirst, TSecond>::Pair(const TFirst& inFirst, const TSecond& inSecond)
		: first(inFirst)
		, second(inSecond)
	{
	}

	template<typename TFirst, typename TSecond>
	constexpr Pair<TFirst, TSecond>::Pair(const TFirst& inFirst, TSecond&& inSecond)
		: first(inFirst)
		, second(Move(inSecond))
	{
	}

	template<typename TFirst, typename TSecond>
	constexpr Pair<TFirst, TSecond>::Pair(TFirst&& inFirst, const TSecond& inSecond)
		: first(Move(inFirst))
		, second(inSecond)
	{
	}

	template<typename TFirst, typename TSecond>
	constexpr Pair<TFirst, TSecond>::Pair(TFirst&& inFirst, TSecond&& inSecond)
		: first(Move(inFirst))
		, second(Move(inSecond))
	{
	}

	template<typename TFirst, typename TSecond>
	constexpr String Pair<TFirst, TSecond>::ToString() const
	{
		String str;

		str.Append("{ ");
		str += jpt::ToString(first);
		str += ", ";
		str += jpt::ToString(second);
		str.Append(" }");

		return str;
	}
}