// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimals/Macros.h"

export module jpt.StrongPtr;

import jpt.TypeDefs;
import jpt.Utilities;
import jpt_private.Deleter;
import jpt_private.ReferenceCounter;
import jpt.WeakPtr;

namespace jpt
{
	/** Retains shared ownership of an object through a pointer. Several StrongPtr objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens: 
		- the last remaining StrongPtr owning the object is destroyed;
		- the last remaining StrongPtr owning the object is assigned another pointer via operator= or Reset(). */
	export template<typename TData>
	class StrongPtr
	{
		friend class WeakPtr<TData>;

	private:
		TData* m_pPtr = nullptr;
		jpt_private::ReferenceCounter* m_pRefCounter = nullptr;

	public:
		constexpr StrongPtr() noexcept = default;
		explicit StrongPtr(TData* pPtr) noexcept;
		StrongPtr(const StrongPtr& other);
		StrongPtr(const WeakPtr<TData>& weakPtr);
		StrongPtr(StrongPtr&& other) noexcept;
		StrongPtr& operator=(const StrongPtr& other);
		StrongPtr& operator=(const WeakPtr<TData>& weakPtr);
		StrongPtr& operator=(StrongPtr&& other) noexcept;
		~StrongPtr();

		template <typename TOther>
		StrongPtr(const StrongPtr<TOther>& other) = delete;

		/** Replaces the managed object with the new pPtr */
		template<typename TDeleter = jpt_private::DefaultDelete<TData>>
		void Reset(TData* pPtr = nullptr, const TDeleter& deleter = TDeleter());

		/** @returns    number of StrongPtr objects referring to the same managed object */
		int32 GetRefCount() const;

		/** @return		Reference or pointer to the managed object */
		constexpr TData& operator*() const noexcept { return *m_pPtr; }
		constexpr TData* operator->() const noexcept { return m_pPtr; }

		/** @return		true if *this owns an object, false otherwise */
		constexpr bool IsValid() const noexcept { return m_pPtr != nullptr; }
		constexpr operator bool() const noexcept { return IsValid(); }

	private:
		/** Resets this->m_pPtr with the passed in pPtr
			Will destroy Ref counter and m_pPtr object if this is the last StrongPtr holding the data */
		template<typename TDeleter = jpt_private::DefaultDelete<TData>>
		void InternalReset(TData* pPtr, const TDeleter& deleter = TDeleter());

		void IncrementStrongRef();
	};

	export template<typename TData, class... TArgs>
	[[nodiscard]] StrongPtr<TData> MakeStrong(TArgs&&... args)
	{
		return StrongPtr<TData>(new TData(jpt::Forward<TArgs>(args)...));
	}

	template<typename TData>
	StrongPtr<TData>::StrongPtr(TData* pPtr) noexcept
		: m_pPtr(pPtr)
		, m_pRefCounter(new jpt_private::ReferenceCounter(1, 0))
	{
	}

	template<typename TData>
	StrongPtr<TData>::StrongPtr(const StrongPtr& other)
		: m_pPtr(other.m_pPtr)
		, m_pRefCounter(other.m_pRefCounter)
	{
		IncrementStrongRef();
	}

	template<typename TData>
	StrongPtr<TData>::StrongPtr(const WeakPtr<TData>& weakPtr)
		: m_pPtr(weakPtr.m_pPtr)
		, m_pRefCounter(weakPtr.m_pRefCounter)
	{
		IncrementStrongRef();
	}

	template<typename TData>
	StrongPtr<TData>::StrongPtr(StrongPtr&& other) noexcept
		: m_pPtr(other.m_pPtr)
		, m_pRefCounter(other.m_pRefCounter)
	{
		other.m_pPtr = nullptr;
		other.m_pRefCounter = nullptr;
	}

	template<typename TData>
	StrongPtr<TData>& StrongPtr<TData>::operator=(const StrongPtr& other)
	{
		if (this != &other)
		{
			InternalReset(other.m_pPtr);
			m_pRefCounter = other.m_pRefCounter;
			IncrementStrongRef();
		}

		return *this;
	}

	template<typename TData>
	StrongPtr<TData>& StrongPtr<TData>::operator=(const WeakPtr<TData>& weakPtr)
	{
		InternalReset(weakPtr.m_pPtr);
		m_pRefCounter = weakPtr.m_pRefCounter;
		IncrementStrongRef();

		return *this;
	}

	template<typename TData>
	StrongPtr<TData>& StrongPtr<TData>::operator=(StrongPtr&& other) noexcept
	{
		if (this != &other)
		{
			InternalReset(other.m_pPtr);
			m_pRefCounter = other.m_pRefCounter;

			other.m_pPtr = nullptr;
			other.m_pRefCounter = nullptr;
		}

		return *this;
	}

	template<typename TData>
	StrongPtr<TData>::~StrongPtr()
	{
		Reset(nullptr);
	}

	template<typename TData>
	int32 StrongPtr<TData>::GetRefCount() const
	{
		if (m_pRefCounter)
		{
			return m_pRefCounter->GetStrongRefs();
		}

		return 0;
	}

	template<typename TData>
	template<typename TDeleter>
	void StrongPtr<TData>::Reset(TData* pPtr, const TDeleter& deleter)
	{
		// If the old pointer was non-empty, deletes the previously managed object
		if (m_pPtr != pPtr)
		{
			InternalReset(pPtr, deleter);

			if (m_pPtr)
			{
				m_pRefCounter = new jpt_private::ReferenceCounter(1, 0);
			}
		}
	}

	template<typename TData>
	template<typename TDeleter>
	void StrongPtr<TData>::InternalReset(TData* pPtr, const TDeleter& deleter)
	{
		if (m_pRefCounter)
		{
			m_pRefCounter->DecrementStrongRef();
			if (!m_pRefCounter->HasAnyRef())
			{
				JPT_DELETE(m_pRefCounter);
			}
		}

		if (!m_pRefCounter || !m_pRefCounter->HasAnyStrongRef())
		{
			deleter(m_pPtr);
		}

		m_pPtr = pPtr;
	}

	template<typename TData>
	void StrongPtr<TData>::IncrementStrongRef()
	{
		if (m_pRefCounter)
		{
			m_pRefCounter->IncrementStrongRef();
		}
	}
}