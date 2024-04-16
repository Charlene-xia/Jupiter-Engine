// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Macros.h"
#include "Debugging/Assert.h"

#include <initializer_list>

export module jpt.HashSet;

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
	template<typename _TValue>
	class HashSet
	{
	public:
		using TValue        = _TValue;
		using TBucket       = LinkedList<TValue>;
		using TBuckets      = DynamicArray<TBucket>;
		using Iterator      = jpt_private::HashTableIterator<TValue>;
		using ConstIterator = jpt_private::ConstHashTableIterator<TValue>;

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

	template<typename TValue>
	constexpr HashSet<TValue>::HashSet(const std::initializer_list<TValue>& list)
	{
		CopyData(list, list.size());
	}

	template<typename TValue>
	constexpr HashSet<TValue>::HashSet(const HashSet& other)
	{
		CopyData(other, other.Count());
	}

	template<typename TValue>
	constexpr HashSet<TValue>::HashSet(HashSet&& other) noexcept
	{
		MoveSet(Move(other));
	}

	template<typename TValue>
	constexpr HashSet<TValue>& HashSet<TValue>::operator=(const HashSet& other)
	{
		if (this != &other)
		{
			Clear();
			CopyData(other, other.Count());
		}

		return *this;
	}

	template<typename TValue>
	constexpr HashSet<TValue>& HashSet<TValue>::operator=(HashSet&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			MoveSet(Move(other));
		}

		return *this;
	}

	template<typename TValue>
	constexpr HashSet<TValue>::~HashSet()
	{
		Clear();
	}

	template<typename TValue>
	constexpr void HashSet<TValue>::Add(const TValue& data)
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
			if (element == data)
			{
				return;
			}
		}

		// If the key does not exist, add it
		++m_count;
		bucket.EmplaceBack(data);
	}

	template<typename TValue>
	constexpr HashSet<TValue>::Iterator HashSet<TValue>::Erase(const TValue& key)
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

	template<typename TValue>
	constexpr  HashSet<TValue>::Iterator HashSet<TValue>::Erase(const Iterator& iterator)
	{
		return Erase(*iterator);
	}

	template<typename TValue>
	constexpr HashSet<TValue>::Iterator HashSet<TValue>::Find(const TValue& key)
	{
		if (IsEmpty())
		{
			return end();
		}

		const size_t index = GetBucketIndex(key);
		TBucket& bucket = m_buckets[index];

		for (typename TBucket::Iterator itr = bucket.begin(); itr != bucket.end(); ++itr)
		{
			if (*itr == key)
			{
				return Iterator(&m_buckets, index, itr);
			}
		}

		return end();
	}

	template<typename TValue>
	constexpr HashSet<TValue>::ConstIterator HashSet<TValue>::Find(const TValue& key) const
	{
		if (IsEmpty())
		{
			return cend();
		}

		const size_t index = GetBucketIndex(key);
		const TBucket& bucket = m_buckets[index];

		for (typename TBucket::ConstIterator itr = bucket.cbegin(); itr != bucket.cend(); ++itr)
		{
			if (*itr == key)
			{
				return ConstIterator(&m_buckets, index, itr);
			}
		}

		return cend();
	}

	template<typename TValue>
	constexpr bool HashSet<TValue>::Contains(const TValue& key) const
	{
		return Find(key) != end();
	}

	template<typename TValue>
	constexpr HashSet<TValue>::Iterator HashSet<TValue>::begin() noexcept
	{
		if (IsEmpty())
		{
			return end();
		}
		return Iterator(&m_buckets, 0, m_buckets.Front().begin());
	}

	template<typename TValue>
	constexpr HashSet<TValue>::Iterator HashSet<TValue>::end() noexcept
	{
		return Iterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue>
	constexpr HashSet<TValue>::ConstIterator HashSet<TValue>::begin() const noexcept
	{
		if (IsEmpty())
		{
			return end();
		}
		return ConstIterator(&m_buckets, 0, m_buckets.Front().begin());
	}

	template<typename TValue>
	constexpr HashSet<TValue>::ConstIterator HashSet<TValue>::end() const noexcept
	{
		return ConstIterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue>
	constexpr HashSet<TValue>::ConstIterator HashSet<TValue>::cbegin() const noexcept
	{
		if (IsEmpty())
		{
			return cend();
		}
		return ConstIterator(&m_buckets, 0, m_buckets.Front().cbegin());
	}

	template<typename TValue>
	constexpr HashSet<TValue>::ConstIterator HashSet<TValue>::cend() const noexcept
	{
		return ConstIterator(&m_buckets, m_buckets.Count(), nullptr);
	}

	template<typename TValue>
	constexpr void HashSet<TValue>::Reserve(size_t capacity)
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

	template<typename TValue>
	constexpr void HashSet<TValue>::Clear()
	{
		m_buckets.Clear();
		m_count = 0;
	}

	template<typename TValue>
	constexpr size_t HashSet<TValue>::GetBucketIndex(const TValue& key) const
	{
		return Hash(key) % m_buckets.Count();
	}

	template<typename TValue>
	constexpr HashSet<TValue>::TBucket& HashSet<TValue>::GetBucket(const TValue& key)
	{
		return m_buckets[GetBucketIndex(key)];
	}

	template<typename TValue>
	constexpr const HashSet<TValue>::TBucket& HashSet<TValue>::GetBucket(const TValue& key) const
	{
		return m_buckets[GetBucketIndex(key)];
	}

	template<typename TValue>
	template<Iterable TContainer>
	constexpr void HashSet<TValue>::CopyData(const TContainer& container, size_t size)
	{
		Reserve(size);

		for (const TValue& data : container)
		{
			TBucket& bucket = GetBucket(data);
			bucket.EmplaceBack(data);
		}

		m_count += size;
	}

	template<typename TValue>
	constexpr void HashSet<TValue>::MoveSet(HashSet&& other)
	{
		m_buckets = Move(other.m_buckets);
		m_count = other.m_count;

		other.m_count = 0;
	}
}