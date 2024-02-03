// Copyright Jupiter Technologies, Inc. All Rights Reserved.

// This file contains minimum C++ programming utility functions.
// Without these functions we can't write a complete program in C++

module;

#include <functional>

export module jpt.Utilities;

import jpt.Concepts;
import jpt.TypeTraits;

export namespace jpt
{
	/** Equivalent of std::move. Returns a rvalue of the object */
	template<Movable T>
	constexpr typename RemoveReference<T>::Type&& Move(T&& object)
	{
		using TCast = RemoveReference<T>::Type;

		static_assert(IsLValueRef<T>, "jpt::move called on an Rvalue");
		static_assert(!IsSameType<TCast&, const TCast&>, "jpt::move called on a const object");

		return static_cast<TCast&&>(object);
	}

	/** Equivalent of std::forward. Return a reference to an rvalue reference. */
	template<class T>
	constexpr T&& Forward(typename RemoveReference<T>::Type& obj)
	{
		return static_cast<T&&>(obj);
	}

	template<class T>
	constexpr T&& Forward(typename RemoveReference<T>::Type&& obj)
	{
		static_assert(!IsLValueRef<T>, "Bad forward call");
		return static_cast<T&&>(obj);
	}

	/** Equivalent for std::swap. Swaps the value of two items */
	template<Movable T>
	constexpr void Swap(T& a, T& b)
	{
		T temp = jpt::Move(b);
		b = jpt::Move(a);
		a = jpt::Move(temp);
	}

	/** Equivalent for std::hash. Calculate the key's hash value */
	template<class KeyT>
	struct Hash
	{
		/** Example: jpt::hash<jpt::string>()(key) */
		size_t operator()(const KeyT& key)
		{
			// TODO: Write my own std::hash
			return std::hash<KeyT>()(key);
		}
	};
}