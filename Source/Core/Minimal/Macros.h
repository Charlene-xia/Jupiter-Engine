// Copyright Jupiter Technologies, Inc. All Rights Reserved.

#pragma once

#pragma region Building
/** Used for hacky fix unused parameters */
#define JPT_IGNORE(...) __VA_ARGS__

/** Turn off optimization */
#define JPT_DEOPTIMIZE __pragma(optimize("", off))

/** Turn on optimization */
#define JPT_REOPTIMIZE __pragma(optimize("", on))

#pragma endregion

#pragma region Memory

/** Deleter helpers */
#define JPT_DELETE(pPointer)\
			delete pPointer;\
			pPointer = nullptr;

#define JPT_DELETE_ARRAY(pPointer)\
			delete[] pPointer;\
			pPointer = nullptr;

#define JPT_SAFE_DELETE(pPointer)\
		if (pPointer)\
		{\
			JPT_DELETE(pPointer);\
		}

#define JPT_SAFE_DELETE_ARRAY(pPointer)\
		if (pPointer)\
		{\
			JPT_DELETE_ARRAY(pPointer);\
		}

/** Helper for clean and delete.
	@param pPointer: Assumed to have Clean() function implemented */
#define JPT_CLEAR_THEN_DELETE(pPointer)\
	pPointer->Clear();\
	JPT_DELETE(pPointer);

	/** Helper for safe cleanand delete.
		@param pPointer: Assumed to have Clean() function implemented */
#define JPT_SAFE_CLEAR_THEN_DELETE(pPointer)\
	if(pPointer)\
	{\
		pPointer->Clear();\
	}\
	JPT_SAFE_DELETE(pPointer);

#pragma endregion

#pragma region Logging

#define JPT_RETURN_VALUE_IF_ERROR(condition, returnValue, ...)\
	if ((condition))\
	{\
		JPT_ERROR(__VA_ARGS__);\
		return returnValue;\
	}

#define JPT_RETURN_VALUE_IF(condition, returnValue)\
	if ((condition))\
	{\
		return returnValue;\
	}

#define JPT_RETURN_FALSE_IF_ERROR(condition, ...)\
	JPT_RETURN_VALUE_IF_ERROR(condition, false, __VA_ARGS__);

#define JPT_RETURN_FALSE_IF(condition)\
	JPT_RETURN_VALUE_IF(condition, false);

#define JPT_RETURN_IF_ERROR(condition, ...)\
	JPT_RETURN_VALUE_IF_ERROR(condition, void(), __VA_ARGS__);

#define JPT_RETURN_IF(condition)\
	JPT_RETURN_VALUE_IF(condition, void());

#define JPT_ERROR_IF(condition, ...)\
	if ((condition))\
	{\
		JPT_ERROR(__VA_ARGS__);\
	}

#define JPT_LOG_IF(condition, ...)\
	if ((condition))\
	{\
		JPT_LOG(__VA_ARGS__);\
	}

#pragma endregion

#pragma region String
/** Combines two strings */
#define JPT_COMBINE_STR(A, B)   A##B

/** Converts a const char* to const wchar_t* by prefixing 'L' */
#define JPT_TO_WSTRING(cStr) L##cStr

/** This solves the issue when dealing with templated string class functions with raw string literals involved. No Heap Memory Allocation at all
	@return   C-Style string for different Char Type but contains the exact input string literals.
	@example: const char* cstr = JPT_GET_PROPER_STRING(char, Hello World);		  // cstr will be "Hello World"
	@example: const wchar_t* wcstr = JPT_GET_PROPER_STRING(wchar_t, Hello World); // wcstr will be L"Hello World" */
#define JPT_GET_PROPER_STRING(TChar, SourceStr)\
	[]() -> const TChar* \
	{\
		const TChar* pString = nullptr; \
		if constexpr (jpt::IsSameType<TChar, char>)\
		{\
			pString = #SourceStr;\
		}\
		else if constexpr (jpt::IsSameType<TChar, wchar_t>)\
		{\
			pString = JPT_TO_WSTRING(#SourceStr);\
		}\
		else\
		{\
			JPT_ASSERT(false, "Unsupported TChar");\
		}\
		return pString;\
	}()

/** Formats a buffer as string 
	@example:
			#include <stdarg.h>
			#include <stdio.h>

			void Foo(const char* format, ...)	// lambda works too
			{
				char buffer[64];	// any size you want
				JPT_FORMAT_STRING(buffer, format, ...);

				// Do something with buffer
			} */
#define JPT_FORMAT_STRING(buffer, format, ...)\
	va_list args;\
	va_start(args, format);\
	vsprintf_s(buffer, format, args);\
	va_end(args)\

#define JPT_FORMAT_WSTRING(buffer, format, ...)\
	va_list args;\
	va_start(args, format);\
	vswprintf_s(buffer, format, args);\
	va_end(args)\

#pragma endregion

#pragma region VA_ARGS

/** @return true if a macro's variadic arguments has passed in parameters. false if it's empty
	@example:
	#define MACRO_WITH_VARIADIC_ARGUMENTS(...)			{ if (JPT_HAS_ARGS(__VA_ARGS__)) { DoStuff(); } }	*/
#define JPT_HAS_ARGS(...) (""#__VA_ARGS__[0] != '\0')



//#define JPT_VA_ARGS_COUNT(...) JPT_VA_ARGS_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)

#pragma endregion

/** @return Count of a plain array.
	@example:
	int intArray[12];
	int intArrayCount = JPT_ARRAY_COUNT(intArray); */
template <typename T, unsigned int kNumber>
char(&ArrayCountHelper(const T(&)[kNumber]))[kNumber + 1];
#define JPT_ARRAY_COUNT(inArray) (sizeof(ArrayCountHelper(inArray)) - 1)