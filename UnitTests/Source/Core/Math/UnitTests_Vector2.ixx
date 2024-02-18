// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Headers.h"

export module UnitTests_Vector2;

import jpt.Vector2;

bool UnitTest_Vec2f()
{
    jpt::Vec2f v;

    v + 1.0f;

    1.0f + v;


    return true;
}

export bool RunUnitTests_Vector2()
{
    JPT_ENSURE(UnitTest_Vec2f(), "UnitTest_Vec2f Failed");

    return true;
}
