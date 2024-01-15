// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include <type_traits>

export module jpt.TypeDefs;

export using uint8  = uint8_t;
export using uint16 = uint16_t;
export using uint32 = uint32_t;
export using uint64 = uint64_t;
export using int8   = int8_t;
export using int16  = int16_t;
export using int32  = int32_t;
export using int64  = int64_t;

export namespace jpt
{
	// Rvalue and Lvalue Utils
	template<typename T> struct RemoveReference              { using Type = T; };
	template<typename T> struct RemoveReference<T&>          { using Type = T; };
	template<typename T> struct RemoveReference<T&&>         { using Type = T; };
	template<typename T> struct RemoveConst                  { using Type = T; };
	template<typename T> struct RemoveConst<const T>         { using Type = T; };
	template<typename T> struct RValueToLValueReference      { using Type = T; };
	template<typename T> struct RValueToLValueReference<T&&> { using Type = T&; };

	template<typename T> constexpr bool IsLValueReferenceType      = false;
	template<typename T> constexpr bool IsLValueReferenceType<T&>  = true;
	template<typename T> constexpr bool IsRValueReferenceType      = false;
	template<typename T> constexpr bool IsRValueReferenceType<T&&> = true;

	// Same type checking
	// Example: jpt::IsSameType<int32, float>
	template<typename A, typename B> constexpr bool IsSameType       = false;
	template<typename A>             constexpr bool IsSameType<A, A> = true;

	/** @return true if the Type is within any of the passed ...Types
		@example:
				int foo = 42;
				double bar = 42.0;
				jpt::IsAnyOf<decltype(foo), float, char, int>; // true	
				jpt::IsAnyOf<decltype(bar), float, char, int>; // false	*/
	template<typename Type, typename ...Types>     
	constexpr bool IsAnyOf = (IsSameType<Type, Types> || ...);

	// enable_if implementation [Deprecated. Use Concepts instead]
	template<bool kCondition, typename ReturnType = void> struct enable_if {};
	template<typename _ReturnType>                        struct enable_if<true, _ReturnType> { using ReturnType = _ReturnType; };
	template<bool kCondition, typename ReturnType = void> using enable_if_t = enable_if<kCondition, ReturnType>::ReturnType;

	// Is Array
	template<typename T>           struct IsArray       { static constexpr bool Value = false; };
	template<typename T>           struct IsArray<T[]>  { static constexpr bool Value = true;  };
	template<typename T, size_t N> struct IsArray<T[N]> { static constexpr bool Value = true;  };
}