﻿// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimals/Headers.h"

export module UnitTests_Logger;

import jpt.CoreModules;

bool UnitTest_Logger_Data()
{
	JPT_LOG("%d", 1);
	JPT_LOG(1);

	JPT_LOG(2);
	JPT_LOG(2.0f);
	JPT_LOG(2.0);
	JPT_LOG(false);
	JPT_LOG(true);
	JPT_LOG('C');
	JPT_LOG('a');
	JPT_LOG("I'm genius");

	class Foo
	{
	public:
		jpt::String ToString() const
		{
			return jpt::String("I am a Foo object");
		}
	};

	Foo foo;
	JPT_LOG(foo);
	JPT_LOG(foo.ToString());
	JPT_LOG(foo.ToString().ConstBuffer());
	JPT_LOG("%s", foo.ToString().ConstBuffer());

	JPT_RETURN_FALSE_IF_ERROR(jpt::ToString(foo) != "I am a Foo object", "");

	return true;
}

export bool RunUnitTests_Logger()
{
	//JPT_RETURN_FALSE_IF_ERROR(!UnitTest_Logger_Data(), "UnitTest_Logger_Data Failed");

	return true;
}