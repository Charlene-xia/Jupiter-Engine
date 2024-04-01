// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Macros.h"
#include "Debugging/Assert.h"
#include "Debugging/Logger.h"

export module jpt.Sorting;

import jpt.Concepts;
import jpt.TypeDefs;
import jpt.Function;
import jpt.Math;
import jpt.Utilities;
import jpt.Limits;

export namespace jpt
{
#pragma region InsertionSort
	template<typename T, typename TComparator>
	constexpr void InsertionSort(T* pBuffer, size_t startIndex, size_t endIndex, TComparator&& comparator)
	{
		for (size_t i = startIndex + 1; i <= endIndex; ++i)
		{
			const T key = pBuffer[i];
			int64 j = static_cast<int64>(i) - 1;

			while (j >= static_cast<int64>(startIndex) && comparator(key, pBuffer[j]))
			{
				pBuffer[j + 1] = pBuffer[j];
				--j;
			}

			pBuffer[j + 1] = key;
		}
	}
#pragma endregion

#pragma region QuickSort
	template<typename T>
	constexpr size_t GetPivot(T* pBuffer, size_t beginIndex, size_t endIndex)
	{
		// Mid of three pivot selection

		// Get each elements
		const T first = pBuffer[beginIndex];
		const T mid = pBuffer[endIndex / 2];
		const T last = pBuffer[beginIndex];

		// Compare and return mid index
		if (first > mid)
		{
			if (mid > last)
				return endIndex / 2;
			else if (first > last)
				return endIndex;
			else
				return beginIndex;
		}
		else
		{
			if (first > last)
				return beginIndex;
			else if (mid > last)
				return endIndex;
			else
				return endIndex / 2;
		}
	}

	template<typename T, typename TComparator>
	constexpr size_t Partition(T* pBuffer, size_t beginIndex, size_t endIndex, TComparator&& comparator)
	{
		size_t pivotIndex = GetPivot(pBuffer, beginIndex, endIndex);
		Swap(pBuffer[pivotIndex], pBuffer[endIndex]);

		const T pivot = pBuffer[endIndex];
		size_t i = beginIndex - 1;	// i is the last element's index of region 1, which is less than the pivot

		// j is the current processing element's index
		for (size_t j = beginIndex; j < endIndex; ++j)
		{
			// if current element should be placed to region one
			// Swap last element in region 1 with current processing element.
			if (comparator(pBuffer[j], pivot))
			{
				++i;
				Swap(pBuffer[i], pBuffer[j]);
			}
		}

		// Everything is in its place except for the pivot. We swap the pivot with the first element of region 2.
		pivotIndex = i + 1;
		Swap(pBuffer[pivotIndex], pBuffer[endIndex]);

		// return the pivot, which becomes the beginning and end points of the next calls to Partition().
		return pivotIndex;
	}

	template<typename T, typename TComparator>
	constexpr void QuickSort(T* pBuffer, size_t beginIndex, size_t endIndex, TComparator&& comparator)
	{
		// Bounds check
		if (beginIndex >= endIndex || endIndex == LimitsOf<size_t>::kMax)
		{
			return;
		}

		// Recursively sort the left and right partitions
		const size_t pivot = Partition(pBuffer, beginIndex, endIndex, Move(comparator));
		QuickSort(pBuffer, beginIndex, pivot - 1, Move(comparator));
		QuickSort(pBuffer, pivot + 1, endIndex, Move(comparator));
	}
#pragma endregion

	template<Trivial T>
	constexpr bool DefaultTrivialComparator(T a, T b) { return a < b; }

	template<NonTrivial T>
	constexpr bool DefaultNonTrivialComparator(const T& a, const T& b) { return a < b; }

	// Raw buffer, Trivial
	template<Trivial T>
	constexpr void Sort(T* pBuffer, size_t size)
	{
		QuickSort(pBuffer, 0, size - 1, DefaultTrivialComparator<T>);
	}
	template<Trivial T, typename TComparator>
	constexpr void Sort(T* pBuffer, size_t size, TComparator&& comparator)
	{
		QuickSort(pBuffer, 0, size - 1, Move(comparator));
	}

	// Raw buffer, NonTrivial
	template<NonTrivial T>
	constexpr void Sort(T* pBuffer, size_t size)
	{
		QuickSort(pBuffer, 0, size - 1, DefaultNonTrivialComparator<T>);
	}
	template<NonTrivial T, typename TComparator>
	constexpr void Sort(T* pBuffer, size_t size, TComparator&& comparator)
	{
		QuickSort(pBuffer, 0, size - 1, Move(comparator));
	}

	// Container, Trivial
	template<ContainingTrivial TContainer>
	constexpr void Sort(TContainer& container)
	{
		QuickSort(container.Buffer(), 0, container.Size() - 1, DefaultTrivialComparator<typename TContainer::TData>);
	}
	template<ContainingTrivial TContainer, typename TComparator>
	constexpr void Sort(TContainer& container, TComparator&& comparator)
	{
		QuickSort(container.Buffer(), 0, container.Size() - 1, Move(comparator));
	}	

	// Container, NonTrivial
	template<ContainingNonTrivial TContainer>
	constexpr void Sort(TContainer& container)
	{
		QuickSort(container.Buffer(), 0, container.Size() - 1, DefaultNonTrivialComparator<typename TContainer::TData>);
	}
	template<ContainingNonTrivial TContainer, typename TComparator>
	constexpr void Sort(TContainer& container, TComparator&& comparator)
	{
		QuickSort(container.Buffer(), 0, container.Size() - 1, Move(comparator));
	}
}