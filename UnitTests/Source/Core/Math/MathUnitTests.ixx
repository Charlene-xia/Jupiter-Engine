// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Building/Headers.h"

export module MathUnitTests;

import jpt.CoreModules;

bool UnitTest_Clamping()
{
	int32 n = jpt::GetClamped(5, 10, 13);
	JPT_RETURN_FALSE_IF_ERROR(n != 10, "");

	jpt::ClampTo(n, 5, 13);
	JPT_RETURN_FALSE_IF_ERROR(n != 10, "");

	jpt::ClampTo(n, 1, 3);
	JPT_RETURN_FALSE_IF_ERROR(n != 3, "");

	return true;
}

bool UnitTest_Abs()
{
	JPT_RETURN_FALSE_IF_ERROR(jpt::GetAbs(-10) != 10, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::GetAbs(10) != 10, "");
	JPT_RETURN_FALSE_IF_ERROR(!jpt::AreValuesClose(jpt::GetAbs(-10.55f), 10.55f) , "");
	JPT_RETURN_FALSE_IF_ERROR(!jpt::AreValuesClose(jpt::GetAbs(10.55f), 10.55f), "");
	return true;
}

bool UnitTest_AreValuesClose()
{
	JPT_RETURN_FALSE_IF_ERROR(!jpt::AreValuesClose(10.556677f, 10.556677f), "");
	JPT_RETURN_FALSE_IF_ERROR(!jpt::AreValuesClose(10.556677f, 10.956677f, 1.0f), "");
	return true;
}

bool UnitTest_MinMax()
{
	JPT_RETURN_FALSE_IF_ERROR(jpt::Min(1, 5) != 1, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::Min(2, 5, 10) != 2, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::Min(5, 1, 2, 5) != 1, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::Max(1, 5) != 5, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::Max(2, 5, 10) != 10, "");
	JPT_RETURN_FALSE_IF_ERROR(jpt::Max(5, 1, 2, 5) != 5, "");

	class Foo
	{
	public:
		Foo() {}
		Foo(const Foo&) {}

		bool operator>(const Foo&) const  {return true;}
		bool operator<(const Foo&) const  {return true;}
		bool operator==(const Foo&) const {return true;}
	};
	Foo f1, f2;
	JPT_RETURN_FALSE_IF_ERROR(jpt::Max(f1, f2) != f1, "");

	return true;
}

export bool RunMathUnitTests()
{
	JPT_RETURN_FALSE_IF_ERROR(!UnitTest_Clamping(), "UnitTest_Clamping Failed");
	JPT_RETURN_FALSE_IF_ERROR(!UnitTest_Abs(), "UnitTest_Abs Failed");
	JPT_RETURN_FALSE_IF_ERROR(!UnitTest_AreValuesClose(), "UnitTest_AreValuesClose Failed");
	JPT_RETURN_FALSE_IF_ERROR(!UnitTest_MinMax(), "UnitTest_MinMax Failed");

	return true;
}