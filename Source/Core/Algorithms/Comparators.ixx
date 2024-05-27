// Copyright Jupiter Technologies, Inc. All Rights Reserved.

export module jpt.Comparators;

import jpt.Concepts;
import jpt.StringUtils;

export namespace jpt
{
	template<typename T = void>
	struct Comparator_Less
	{
		template<NonTrivial U = T>
		constexpr bool operator()(const U& lhs, const U& rhs) const
		{
			return lhs < rhs;
		}

		template<Trivial U = T>
		constexpr bool operator()(U lhs, U rhs) const
		{
			return lhs < rhs;
		}
	};

	template<typename T = void>
	struct Comparator_Greater
	{
		template<NonTrivial U = T>
		constexpr bool operator()(const U& lhs, const U& rhs) const
		{
			return lhs > rhs;
		}

		template<Trivial U = T>
		constexpr bool operator()(U lhs, U rhs) const
		{
			return lhs > rhs;
		}
	};

	template<typename T = void>
	struct Comparator_Equal
	{
		template<NonTrivial U = T>
		constexpr bool operator()(const U& lhs, const U& rhs) const
		{
			return lhs == rhs;
		}

		template<Trivial U = T>
		constexpr bool operator()(U lhs, U rhs) const
		{
			return lhs == rhs;
		}
	};

	template<>
	struct Comparator_Equal<const char*>
	{
		constexpr bool operator()(const char* lhs, const char* rhs) const
		{
			return AreStringsSame(lhs, rhs);
		}
	};

	template<>
	struct Comparator_Equal<const wchar_t*>
	{
		constexpr bool operator()(const wchar_t* lhs, const wchar_t* rhs) const
		{
			return AreStringsSame(lhs, rhs);
		}
	};
}