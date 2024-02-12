// Copyright Jupiter Technologies, Inc. All Rights Reserved.

export module jpt.Variant;

import jpt.Allocator;
import jpt.Byte;
import jpt.TypeTraits;
import jpt.TypeDefs;
import jpt.Math;
import jpt.Limits;

export namespace jpt
{
	template<typename...TArgs>
	class Variant
	{
		using TIndex = uint8;

		static constexpr size_t kMaxTypeSize = Max(sizeof(TArgs)...);	/**< The biggest size amoung TArgs */
		static constexpr TIndex kTypesCount  = sizeof...(TArgs);	    /**< Count of TArgs */

		static_assert(kTypesCount > 0, "Variant must have at least one type");

	private:
		Byte m_buffer[kMaxTypeSize];    /**< The buffer to store the value of the Variant. Sized by the biggest type */
		TIndex m_currentIndex = kInvalidValue<TIndex>;  /**< The current using index in m_typeInfos */

	public:
		constexpr Variant() = default;
		constexpr ~Variant();

		template<typename T>
		constexpr Variant(const T& value);

		template<typename T>
		constexpr Variant& operator=(const T& value);

		template<typename T> constexpr       T& As();
		template<typename T> constexpr const T& As() const;

	private:
		template<typename T>
		constexpr void Construct(const T& value);

		template<typename TCurrent, typename ...TRest>
		constexpr void Destruct();

		/** @return		The index of the TypeToFind in TArgs */
		template<typename TypeToFind, typename TCurrent, typename ...TRest>
		constexpr TIndex GetIndexOfType() const;
	};

	template<typename ...TArgs>
	constexpr Variant<TArgs...>::~Variant()
	{
		Destruct<TArgs...>();
	}

	template<typename ...TArgs>
	template<typename T>
	constexpr Variant<TArgs...>::Variant(const T& value)
	{
		Construct<T>(value);
	}

	template<typename ...TArgs>
	template<typename T>
	constexpr Variant<TArgs...>& Variant<TArgs...>::operator=(const T& value)
	{
		Destruct<TArgs...>();
		Construct<T>(value);
		return *this;
	}

	template<typename ...TArgs>
	template<typename T>
	constexpr T& Variant<TArgs...>::As()
	{
		static_assert(IsAnyOf<T, TArgs...>, "T is not in this variant TArgs list");
		return reinterpret_cast<T&>(m_buffer);
	}

	template<typename ...TArgs>
	template<typename T>
	constexpr const T& Variant<TArgs...>::As() const
	{
		static_assert(IsAnyOf<T, TArgs...>, "T is not in this variant TArgs list");
		return reinterpret_cast<const T&>(m_buffer);
	}

	template<typename ...TArgs>
	template<typename T>
	constexpr void Variant<TArgs...>::Construct(const T& value)
	{
		static_assert(IsAnyOf<T, TArgs...>, "T is not in this variant TArgs list");

		Allocator<T>::Construct(reinterpret_cast<T*>(&m_buffer), value);
		m_currentIndex = GetIndexOfType<T, TArgs...>();
	}

	template<typename ...TArgs>
	template<typename TCurrent, typename ...TRest>
	constexpr void Variant<TArgs...>::Destruct()
	{
		if (m_currentIndex == kTypesCount - sizeof...(TRest) - 1)
		{
			Allocator<TCurrent>::Destruct(reinterpret_cast<TCurrent*>(&m_buffer));
			m_currentIndex = kInvalidValue<TIndex>;
		}

		if constexpr (sizeof...(TRest) > 0)
		{
			Destruct<TRest...>();
		}
	}

	template<typename ...TArgs>
	template<typename TypeToFind, typename TCurrent, typename ...TRest>
	constexpr Variant<TArgs...>::TIndex Variant<TArgs...>::GetIndexOfType() const
	{
		if constexpr (IsSameType<TypeToFind, TCurrent>)
		{
			return kTypesCount - sizeof...(TRest) - 1;
		}
		else
		{
			return GetIndexOfType<TypeToFind, TRest...>();
		}
	}
}