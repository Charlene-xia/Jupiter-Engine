// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/CoreMacros.h"

export module jpt.Math;

import jpt.Concepts;
import jpt.Constants;
import jpt.TypeDefs;
import jpt.Utilities;

export namespace jpt
{
#pragma region Clamping
	/** @return Clamped value. Ensure it's at least bigger than min and smaller than max. Exclusive */
	template<ComparableTrivial T>
	constexpr T Clamp(T value, T min, T max)
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}
		return value;
	}
	template<ComparableNonTrivial T>
	constexpr T Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}
		return value;
	}

	/** Clamps a value. Ensure it's at least bigger than min and smaller than max. Exclusive
		@param outValue:	Will be changed if less than min or bigger than max */
	template<ComparableTrivial T>
	constexpr void ClampTo(T& outValue, T min, T max)
	{
		if (outValue < min)
		{
			outValue = min;
		}
		else if (outValue > max)
		{
			outValue = max;
		}
	}
	template<ComparableNonTrivial T>
	constexpr void ClampTo(T& outValue, const T& min, const T& max)
	{
		if (outValue < min)
		{
			outValue = min;
		}
		else if (outValue > max)
		{
			outValue = max;
		}
	}

#pragma endregion Clamping

#pragma region Lerp
	template<NonTrivial T, Floating TFloat = float32>
	constexpr T Lerp(const T& start, const T& end, TFloat t)
	{
		return start + t * (end - start);
	}
	template<Trivial T, Floating TFloat = float32>
	constexpr T Lerp(T start, T end, TFloat t)
	{
		return start + t * (end - start);
	}
	template<NonTrivial T, Floating TFloat = float32>
	constexpr void Lerp(T& value, const T& start, const T& end, TFloat t)
	{
		value = start + t * (end - start);
	}
	template<Trivial T, Floating TFloat = float32>
	constexpr void Lerp(T& value, T start, T end, TFloat t)
	{
		value = start + t * (end - start);
	}

	template<NonTrivial T>
	constexpr T InvLerp(const T& start, const T& end, const T& value)
	{
		return (value - start) / (end - start);
	}
	template<Trivial T>
	constexpr T InvLerp(T start, T end, T value)
	{
		return (value - start) / (end - start);
	}
#pragma endregion Lerp

#pragma region MinMax

	template <Trivial TFirst, typename... TRest>
	constexpr TFirst Min(TFirst first, TRest... inputs)
	{
		TFirst smallestVal = first;

		([&]
			{
				if (smallestVal > inputs)
				{
					smallestVal = inputs;
				}
			} (), ...);

		return smallestVal;
	}
	template <NonTrivial TFirst, typename... TRest>
	constexpr TFirst Min(const TFirst& first, const TRest&... inputs)
	{
		TFirst smallestVal = first;

		([&]
			{
				if (smallestVal > inputs)
				{
					smallestVal = inputs;
				}
			} (), ...);

		return smallestVal;
	}

	template <Trivial TFirst, typename... TRest>
	constexpr TFirst Max(TFirst first, TRest... inputs)
	{
		TFirst largestVal = first;

		([&]
			{
				if (largestVal < inputs)
				{
					largestVal = inputs;
				}
			} (), ...);

		return largestVal;
	}
	template <NonTrivial TFirst, typename... TRest>
	constexpr TFirst Max(const TFirst& first, const TRest&... inputs)
	{
		TFirst largestVal = first;

		([&]
			{
				if (largestVal < inputs)
				{
					largestVal = inputs;
				}
			} (), ...);

		return largestVal;
	}

#pragma endregion MinMax

	/** @return The absolute value of input arithmetic parameter */
	template<Numeric TNum>
	constexpr TNum Abs(TNum value)
	{
		return (value >= static_cast<TNum>(0) ? value : -value);
	}

	/** @return true if two values are close enough */
	template<Integral TInt1, Integral TInt2>
	constexpr bool AreValuesClose(TInt1 A, TInt2 B, TInt1 tolerance = static_cast<TInt1>(0))
	{
		return Abs(A - static_cast<TInt1>(B)) <= tolerance;
	}

	template<Floating TFloat1, Floating TFloat2>
	constexpr bool AreValuesClose(TFloat1 A, TFloat2 B, TFloat1 tolerance = static_cast<TFloat1>(0.000001))
	{
		return Abs(A - static_cast<TFloat1>(B)) <= tolerance;
	}

	template<Floating TFloat = float32>
	constexpr TFloat ToDegrees(TFloat radians)
	{
		return radians * static_cast<TFloat>(180) / kPi<TFloat>;
	}
	template<Floating TFloat = float32>
	constexpr TFloat ToRadians(TFloat degrees)
	{
		return degrees * kPi<TFloat> / static_cast<TFloat>(180);
	}
}