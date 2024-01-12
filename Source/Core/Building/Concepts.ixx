// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include <type_traits>
#include <iostream>

export module jpt.Concepts;

import jpt.Constants;
import jpt.TypeDefs;

export namespace jpt
{
	template<typename T>
	concept Numeric = std::is_arithmetic_v<T>;

	template<typename T>
	concept Integral = std::is_integral_v<T>;

	template<typename T>
	concept Floating = std::is_floating_point_v<T>;

	template<typename T>
	concept StringLiteral = IsSameType<T, char> || IsSameType<T, wchar_t>;

	template<typename T>
	concept Copyable = std::is_copy_constructible_v<T>;

	template<typename T>
	concept Movable = std::is_move_constructible_v<T>;

	template<typename T>
	concept Primitive = std::is_fundamental_v<T> || StringLiteral<T>;

	template<typename T>
	concept Trivial = std::is_trivially_constructible_v<T> &&
					  std::is_trivially_copy_constructible_v<T> &&
					  sizeof(T) <= kLargeDataSize;

	template<typename T>
	concept NonTrivial = !std::is_trivially_constructible_v<T> ||
		                 !std::is_trivially_copy_constructible_v<T> ||
		                 sizeof(T) > kLargeDataSize;

	template<typename T>
	concept Comparable = requires(T left, T right)
	{
		left < right;
		left > right;
	};

	/** Avoid copy-constructing when comparing non-trivially copiable objects */
	template<typename T>
	concept ComparableTrivial = Comparable<T> && Trivial<T>;

	template<typename T>
	concept ComparableNonTrivial = Comparable<T> && NonTrivial<T>;

	template<typename T>
	concept EnabledToString = !Primitive<T> && requires(T object) { object.ToString(); };

	template<typename T>
	concept DisabledToString = std::is_fundamental_v<T> || !EnabledToString<T>;

	template<typename T>
	concept EnabledCout = requires(T object) { std::cout << object; };
}