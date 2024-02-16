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
	/** Returns a rvalue of the object */
	template<MoveConstructible T>
	constexpr typename RemoveReference<T>::Type&& Move(T&& object)
	{
		using TCast = RemoveReference<T>::Type;

		static_assert(IsLValueRef<T>, "jpt::Move called on an Rvalue");
		static_assert(!IsSameType<TCast&, const TCast&>, "jpt::Move called on a const object");

		return static_cast<TCast&&>(object);
	}

	/** Returns LValue if obj is LValue, Returns RValue if obj is RValue */
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

	template<typename ...Ts>
	constexpr size_t GetArgsCount(Ts&&... args)
	{
		return (0 + ... + (void(args), 1));
	}
}