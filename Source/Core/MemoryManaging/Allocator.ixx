// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include <stdlib.h>
#include <cstring>
#include <initializer_list>

export module jpt.Allocator;

import jpt.Utilities;

export namespace jpt
{
	/** Allocate and deallocate memory for objects. 
		@see https://www.codeproject.com/Articles/4795/C-Standard-Allocator-An-Introduction-and-Implement
		@see https://learn.microsoft.com/en-us/cpp/standard-library/allocators?view=msvc-170#writing-your-own-allocator-c11 
		@see https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples */
	template<typename T>
	class Allocator
	{
	public:
		Allocator() = default;

		template<class OtherT>
		Allocator(const Allocator<OtherT>& other) noexcept {}

	public:
		/** Allocates plain heap memory for desired amount of memory for <Type>
			@param count		How many <Type> objects to allocate */
		static T* Allocate(size_t count = 1);
		static T* AllocateArray(size_t count, const std::initializer_list<T>& values = {});

		/** Allocates heap memory for one <Type>, with initializing value */
		static T* AllocateWithValue(const T& data);

		/** Allocates heap memory for desired amount of memory for <Type> with init values
			@param count		How many <Type> objects to allocate 
			@param values		An pointer to an array for each allocated objects initializing value. */
		static T* AllocateMultiWithValue(size_t count, const T* pValues);
		static T* AllocateMultiWithValue(size_t count, const std::initializer_list<T>& values);

		/** Deallocate memory for the passed in pointer */
		static void Deallocate(T* pPointer);
		static void DeallocateArray(T* pArray);

		static void Construct(T* pPointer, const T& object);
		static void Destruct(T* pPointer);

		template<class OtherT>
		bool operator==(const Allocator<OtherT>&) const noexcept;

		template<class OtherT>
		bool operator!=(const Allocator<OtherT>&) const noexcept;
	};

	template<typename T>
	T* Allocator<T>::Allocate(size_t count /* = 1 */ )
	{
		return static_cast<T*>(::operator new(count * sizeof(T)));
	}

	template<typename T>
	T* Allocator<T>::AllocateArray(size_t count, const std::initializer_list<T>& values/* = {}*/)
	{
		T* pArray = static_cast<T*>(::operator new[](count * sizeof(T)));

		size_t i = 0;
		for (auto itr = values.begin(); itr != values.end(); ++itr)
		{
			pArray[i] = *itr;
			++i;
		}

		return pArray;
	}

	template<typename T>
	T* Allocator<T>::AllocateWithValue(const T& data)
	{
		T* pPointer = static_cast<T*>(::operator new(sizeof(T)));
		*pPointer = data;
		return pPointer;
	}

	template<typename T>
	T* Allocator<T>::AllocateMultiWithValue(size_t count, const T* pValues)
	{
		T* pArray = static_cast<T*>(::operator new(count * sizeof(T)));
		std::memcpy(pArray, pValues, count * sizeof(T));
		return pArray;
	}

	template<typename T>
	T* Allocator<T>::AllocateMultiWithValue(size_t count, const std::initializer_list<T>& values)
	{
		T* pArray = static_cast<T*>(::operator new(count * sizeof(T)));

		size_t i = 0;
		for (auto itr = values.begin(); itr != values.end(); ++itr)
		{
			pArray[i] = *itr;
			++i;
		}

		return pArray;
	}

	template<typename T>
	void Allocator<T>::Deallocate(T* pPointer)
	{
		::operator delete(pPointer);
	}

	template<typename T>
	void Allocator<T>::DeallocateArray(T* pArray)
	{
		::operator delete[](pArray);
	}

	template<typename T>
	void Allocator<T>::Construct(T* pPointer, const T& object)
	{
		new(pPointer) T(object);
	}

	template<typename T>
	void Allocator<T>::Destruct(T* pPointer)
	{
		pPointer->~Type();
	}

	template<typename T>
	template<class OtherType>
	bool Allocator<T>::operator==(const Allocator<OtherType>&) const noexcept
	{
		return true;
	}

	template<typename T>
	template<class OtherType>
	bool Allocator<T>::operator!=(const Allocator<OtherType>&) const noexcept
	{
		return false;
	}
}