// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Headers.h"

export module UnitTests_Core;

/** Unit Test Modules */

// Minimal
import UnitTests_Macros;
import jpt.Utilities;

// Algorithms
import UnitTests_Sorting;
import UnitTests_Searching;

// Containers
import UnitTests_HashMap;
import UnitTests_LinkedList;
import UnitTests_DynamicArray;
import UnitTests_StaticArray;

// Functional
import UnitTests_Slot;
import UnitTests_Function;

// Utilities
import UnitTests_Utilities;
import UnitTests_TypeTraits;

// Math
import UnitTests_Vector3;
import UnitTests_Vector2;
import UnitTests_Math;
import UnitTests_RandomNumberGenerator;

// Memory Managing
import UnitTests_Allocator;
import UnitTests_StrongPtr;
import UnitTests_UniquePtr;
import UnitTests_WeakPtr;

// Strings
import UnitTests_StringUtils;
import UnitTests_String;
import UnitTests_StringView;

// Types
import UnitTests_Enum_Global;
import UnitTests_Any;
import UnitTests_Byte;
import UnitTests_Variant;
import UnitTests_Optional;
import UnitTests_Enum;
import UnitTests_Tuple;
import UnitTests_Pair;

export bool RunUnitTests_Core()
{
	/** Unit Test Functions */
	
	// Algorithms
	JPT_ENSURE(RunUnitTests_Sorting());
	JPT_ENSURE(RunUnitTests_Searching());

	// Containers
	JPT_ENSURE(RunUnitTests_HashMap());
	JPT_ENSURE(RunUnitTests_LinkedList());
	JPT_ENSURE(RunUnitTests_DynamicArray());
	JPT_ENSURE(RunUnitTests_StaticArray());

	// Functional
	JPT_ENSURE(RunUnitTests_Slot());
	JPT_ENSURE(RunUnitTests_Function());

	// Minimal
	JPT_ENSURE(RunUnitTests_Utilities());
	JPT_ENSURE(RunUnitTests_TypeTraits());
	JPT_ENSURE(RunUnitTests_Macros());

	// Math
	JPT_ENSURE(RunUnitTests_Vector3());
	JPT_ENSURE(RunUnitTests_Vector2());
	JPT_ENSURE(RunUnitTests_Math());
	JPT_ENSURE(RunUnitTests_RandomNumberGenerator());

	// Memory Managing
	JPT_ENSURE(RunUnitTests_Allocator());
	JPT_ENSURE(RunUnitTests_StrongPtr());
	JPT_ENSURE(RunUnitTests_UniquePtr());
	JPT_ENSURE(RunUnitTests_WeakPtr());

	// Strings
	JPT_ENSURE(RunUnitTests_String());
	JPT_ENSURE(RunUnitTests_StringUtils());
	JPT_ENSURE(RunUnitTests_StringView());

	// Types
	JPT_ENSURE(RunUnitTests_Any());
	JPT_ENSURE(RunUnitTests_Byte());
	JPT_ENSURE(RunUnitTests_Variant());
	JPT_ENSURE(RunUnitTests_Optional());
	JPT_ENSURE(RunUnitTests_Enum());
	JPT_ENSURE(RunUnitTests_Tuple());
	JPT_ENSURE(RunUnitTests_Pair());

	return true;
}