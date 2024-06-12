// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Macros.h"
#include "Debugging/Assert.h"

#include <initializer_list>

export module jpt.HashSet;

import jpt.Comparators;
import jpt.Concepts;
import jpt.Constants;
import jpt.DynamicArray;
import jpt.Hash;
import jpt.LinkedList;
import jpt.Math;
import jpt.Utilities;

import jpt_private.HashTableIterator;

export namespace jpt
{
	/** A hash set is a collection of unique elements. The order of the elements in a hash set is undefined. */
	template<typename _TValue, typename _Comparator = Comparator_Equal<_TValue>>
	class HashSet
	{
	public:
		using TValue        = _TValue;
		using TComparator   = _Comparator;
		using TBucket       = LinkedList<TValue>;
		using TBuckets      = DynamicArray<TBucket>;
		using Iterator      = jpt_private::HashTableIterator<TValue>;
		using ConstIterator = jpt_private::ConstHashTableIterator<TValue>;

	private:
		static constexpr TComparator kComparator = TComparator();

	private:
		TBuckets m_buckets;
		size_t   m_count = 0;

	public:
		constexpr HashSet() noexcept = default;
		constexpr HashSet(const std::initializer_list<TValue>& list);
		constexpr HashSet(const HashSet& other);
		constexpr HashSet(HashSet&& other) noexcept;
		constexpr HashSet& operator=(const HashSet& other);
		constexpr HashSet& operator=(HashSet&& other) noexcept;
		constexpr ~HashSet();

		// Iterators
		constexpr Iterator begin() noexcept;
		constexpr Iterator end()   noexcept;
		constexpr ConstIterator begin()  const noexcept;
		constexpr ConstIterator end()    const noexcept;
		constexpr ConstIterator cbegin() const noexcept;
		constexpr ConstIterator cend()   const noexcept;

		// Capacity
		constexpr size_t Count()  const { return m_count; }
		constexpr bool IsEmpty() const { return m_count == 0; }
		constexpr void Reserve(size_t capacity);

		// Modifiers
		constexpr void Add(const TValue& data);
		constexpr Iterator Erase(const TValue& data);
		constexpr Iterator Erase(const Iterator& iterator);
		constexpr void Clear();

		// Searching
		constexpr Iterator      Find(const TValue& key);
		constexpr ConstIterator Find(const TValue& key) const;
		constexpr bool Contains(const TValue& key) const;

	protected:
		constexpr size_t GetBucketIndex(const TValue& key) const;
		constexpr       TBucket& GetBucket(const TValue& key);
		constexpr const TBucket& GetBucket(const TValue& key) const;

		template<Iterable TContainer>
		constexpr void CopyData(const TContainer& container, size_t size);

		constexpr void MoveSet(HashSet&& other);
	};

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::HashSet(const std::initializer_list<TValue>& list)
	{
		CopyData(list, list.size());
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::HashSet(const HashSet& other)
	{
		CopyData(other, other.Count());
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::HashSet(HashSet&& other) noexcept
	{
		MoveSet(Move(other));
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>& HashSet<TValue, TComparator>::operator=(const HashSet& other)
	{
		if (this != &other)
		{
			Clear();
			CopyData(other, other.Count());
		}

		return *this;
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>& HashSet<TValue, TComparator>::operator=(HashSet&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			MoveSet(Move(other));
		}

		return *this;
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::~HashSet()
	{
		Clear();
	}

	template<typename TValue, typename TComparator>
	constexpr void HashSet<TValue, TComparator>::Add(const TValue& data)
	{
		// Grow if needed
		if (m_count >= m_buckets.Count() * kGrowMultiplier)
		{
			Reserve(m_count * kGrowMultiplier);
		}

		TBucket& bucket = GetBucket(data);

		// Check if the key already exists. If it does, return
		for (TValue& element : bucket)
		{
			if (kComparator(element, data))
			{
				return;
			}
		}

		// If the key does not exist, add it
		++m_count;
		bucket.EmplaceBack(data);
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::Iterator HashSet<TValue, TComparator>::Erase(const TValue& key)
	{
		if (Iterator itr = Find(key); itr != end())
		{
			Iterator nextItr = itr + 1;

			TBucket& bucket = m_buckets[itr.GetIndex()];
			bucket.Erase(itr.GetIterator());
			--m_count;

			return nextItr;
		}

		return end();
	}

	template<typename TValue, typename TComparator>
	constexpr  HashSet<TValue, TComparator>::Iterator HashSet<TValue, TComparator>::Erase(const Iterator& iterator)
	{
		return Erase(*iterator);
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::Iterator HashSet<TValue, TComparator>::Find(const TValue& key)
	{
		if (IsEmpty())
		{
			return end();
		}

		const size_t index = GetBucketIndex(key);
		TBucket& bucket = m_buckets[index];

		for (typename TBucket::Iterator itr = bucket.begin(); itr != bucket.end(); ++itr)
		{
			if (kComparator(*itr, key))
			{
				return Iterator(&m_buckets, index, itr);
			}
		}

		return end();
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::ConstIterator HashSet<TValue, TComparator>::Find(const TValue& key) const
	{
		if (IsEmpty())
		{
			return cend();
		}

		const size_t index = GetBucketIndex(key);
		const TBucket& bucket = m_buckets[index];

		for (typename TBucket::ConstIterator itr = bucket.cbegin(); itr != bucket.cend(); ++itr)
		{
			if (kComparator(*itr, key))
			{
				return ConstIterator(&m_buckets, index, itr);
			}
		}

		return cend();
	}

	template<typename TValue, typename TComparator>
	constexpr bool HashSet<TValue, TComparator>::Contains(const TValue& key) const
	{
		return Find(key) != end();
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::Iterator HashSet<TValue, TComparator>::begin() noexcept
	{
		if (IsEmpty())
		{
			return end();
		}
		return Iterator(&m_buckets, 0, m_buckets.Front().begin());
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::Iterator HashSet<TValue, TComparator>::end() noexcept
	{
		return Iterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::ConstIterator HashSet<TValue, TComparator>::begin() const noexcept
	{
		if (IsEmpty())
		{
			return end();
		}
		return ConstIterator(&m_buckets, 0, m_buckets.Front().begin());
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::ConstIterator HashSet<TValue, TComparator>::end() const noexcept
	{
		return ConstIterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::ConstIterator HashSet<TValue, TComparator>::cbegin() const noexcept
	{
		if (IsEmpty())
		{
			return cend();
		}
		return ConstIterator(&m_buckets, 0, m_buckets.Front().cbegin());
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::ConstIterator HashSet<TValue, TComparator>::cend() const noexcept
	{
		return ConstIterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue, typename TComparator>
	constexpr void HashSet<TValue, TComparator>::Reserve(size_t capacity)
	{
		static constexpr size_t kMinCapacity = 8;

		TBuckets oldDataCopy = m_buckets;
		m_buckets.Clear();
		m_buckets.Resize(Max(kMinCapacity, capacity));

		for (const TBucket& bucket : oldDataCopy)
		{
			for (const TValue& element : bucket)
			{
				const size_t index = GetBucketIndex(element);
				m_buckets[index].EmplaceBack(element);
			}
		}
	}

	template<typename TValue, typename TComparator>
	constexpr void HashSet<TValue, TComparator>::Clear()
	{
		m_buckets.Clear();
		m_count = 0;
	}

	template<typename TValue, typename TComparator>
	constexpr size_t HashSet<TValue, TComparator>::GetBucketIndex(const TValue& key) const
	{
		return Hash(key) % m_buckets.Count();
	}

	template<typename TValue, typename TComparator>
	constexpr HashSet<TValue, TComparator>::TBucket& HashSet<TValue, TComparator>::GetBucket(const TValue& key)
	{
		return m_buckets[GetBucketIndex(key)];
	}

	template<typename TValue, typename TComparator>
	constexpr const HashSet<TValue, TComparator>::TBucket& HashSet<TValue, TComparator>::GetBucket(const TValue& key) const
	{
		return m_buckets[GetBucketIndex(key)];
	}

	template<typename TValue, typename TComparator>
	template<Iterable TContainer>
	constexpr void HashSet<TValue, TComparator>::CopyData(const TContainer& container, size_t size)
	{
		Reserve(m_count + size);

		for (const TValue& data : container)
		{
			TBucket& bucket = GetBucket(data);
			bucket.EmplaceBack(data);
		}

		m_count += size;
	}

	template<typename TValue, typename TComparator>
	constexpr void HashSet<TValue, TComparator>::MoveSet(HashSet&& other)
	{
		m_buckets = Move(other.m_buckets);
		m_count = other.m_count;

		other.m_count = 0;
	}
}