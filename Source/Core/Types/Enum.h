// Copyright Jupiter Technologies, Inc. All Rights Reserved.

#pragma once

import jpt.TypeDefs;
import jpt.String;
import jpt.StringUtils;
import jpt.HashMap;
import jpt.DynamicArray;
import jpt.Limits;

/** If an Enum ran out of space later, change this to a larger uint */
using TEnumSize = uint8; 

/** Contains shared enum data across all instances and public */
struct EnumData
{
	TEnumSize count = 0;	/**< How many values this enum has */
	TEnumSize min = jpt::LimitsOf<TEnumSize>::kMax;	/**< The min value of this enum */
	TEnumSize max = jpt::LimitsOf<TEnumSize>::kMin;	/**< The max value of this enum */
	jpt::HashMap<TEnumSize, jpt::String> names;		/**< The names map of the enum values */
};

/** Generate the shared enum data 
	@param pSource		A string contains all the enum values, separated by ',' accepts value assignment too */
EnumData GenerateData(const char* pSource);

#define JPT_ENUM(EnumName, ...)\
class EnumName\
{\
public:\
	enum EValues : TEnumSize\
	{\
		__VA_ARGS__\
	};\
	\
private:\
	static const EnumData s_data;\
	TEnumSize m_value = 0;	/**< The actual enum value of one instance */ \
	\
public:\
	/** Static global API. See EnumData for more details at Enum.h */\
	/**	@example: EFoo::Count() */\
	\
	constexpr static TEnumSize Count() { return s_data.count; }\
	constexpr static TEnumSize Min()   { return s_data.min; }\
	constexpr static TEnumSize Max()   { return s_data.max; }\
	constexpr static const jpt::HashMap<TEnumSize, jpt::String>& Names() { return s_data.names; }\
	constexpr static const jpt::String& Name(TEnumSize index);\
	\
public:\
	/** Member API */\
	constexpr EnumName(TEnumSize data);\
	constexpr EnumName& operator=(TEnumSize data);\
	\
	/** Modifier */\
	/** If you are using ++/--. Make sure your enum values is linear and contiguous, otherwise you will have assertion failed */\
	/**	Good example: JPT_ENUM(EDemo, A, B, C); JPT_ENUM(EDemo, A = 2, B, C);			// All good */\
	/**	Bad  example: JPT_ENUM(EDemo, A, B = 3, C); JPT_ENUM(EDemo, A = 2, B, C = 5);	// Error!	*/\
	constexpr EnumName& operator++();\
	constexpr EnumName& operator--();\
	\
	/** Iteration */\
	/** Supports range-based, iterated, and numeric if items are linear and contigous */\
	constexpr auto begin()  const { return s_data.names.begin();  }\
	constexpr auto end()    const { return s_data.names.end();    }\
	constexpr auto cbegin() const { return s_data.names.cbegin(); }\
	constexpr auto cend()   const { return s_data.names.cend();   }\
	\
	/** Comparison */\
	template<jpt::Integral TInt>\
	constexpr bool operator==(TInt value) const;\
	constexpr bool operator==(const char* str) const;\
	\
	/** Numeric value access */\
	constexpr TEnumSize Value()    const { return m_value; }\
	constexpr operator TEnumSize() const { return m_value; }\
	\
	/** String value access */\
	constexpr const jpt::String& ToString()  const { return s_data.names[m_value]; }\
	constexpr operator const jpt::String&()  const { return s_data.names[m_value]; }\
};\
\
const EnumData EnumName::s_data = GenerateData(#__VA_ARGS__);\
\
constexpr EnumName::EnumName(TEnumSize data)\
	: m_value(data)\
{\
}\
\
constexpr EnumName& EnumName::operator=(TEnumSize data)\
{\
	m_value = data;\
	return *this;\
}\
\
constexpr EnumName& EnumName::operator++()\
{\
	++m_value;\
	JPT_ASSERT(s_data.names.Contains(m_value));\
	return *this;\
}\
\
constexpr EnumName& EnumName::operator--()\
{\
	--m_value;\
	JPT_ASSERT(s_data.names.Contains(m_value));\
	return *this;\
}\
\
template<jpt::Integral TInt>\
constexpr bool EnumName::operator==(TInt value) const\
{\
	return m_value == static_cast<TEnumSize>(value);\
}\
\
constexpr bool EnumName::operator==(const char* str) const\
{\
	return ToString() == str;\
}\
\
constexpr const jpt::String& EnumName::Name(TEnumSize index)\
{\
	JPT_ASSERT(s_data.names.Contains(index));\
	return s_data.names[index];\
}

