// Copyright Jupiter Technologies, Inc. All Rights Reserved.

#pragma once

import jpt.TypeDefs;
import jpt.DynamicArray;
import jpt.StaticArray;
import jpt.String;
import jpt.Utilities;
import jpt.HashMap;

void BuildNames(jpt::HashMap<uint8, jpt::String>& namesMap, uint8& count, uint8& start, const char* pSource);

struct EnumData
{
	size_t count;
	size_t start;
	jpt::HashMap<uint8, jpt::String> names;
};

	/** An Enum class supports the following operations:
		- operator++/--: prefix and postfix increment/decrement
		- ToString(): returns the string representation of the enum
		- FromString(): returns the enum value from the string representation
	*/
#define JPT_ENUM(EnumName, ...)\
class EnumName\
{\
public:\
	using TSize = uint8; /* If ran out of space later, change this to larger uint */ \
	\
	enum EData : uint8\
	{\
		__VA_ARGS__ \
	};\
	\
	static jpt::HashMap<uint8, jpt::String> s_names;\
	static size_t Count;\
	static size_t Start;\
	\
private:\
	TSize m_value = 0;\
	\
public:\
	EnumName()\
	{\
		\
	}\
	\
	EnumName(EData data)\
		: m_value(data)\
	{\
		\
	}\
	\
	EnumName& operator=(EData data)\
	{\
		m_value = data;\
		return *this;\
	}\
};\
\
size_t EnumName::Count = 0;\
size_t EnumName::Start = 0;
