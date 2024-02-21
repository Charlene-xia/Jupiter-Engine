// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Headers.h"

#include <chrono>

#if IS_PLATFORM_WIN64
    #include <Windows.h>
#endif

export module UnitTests_Timing;

import jpt.Timing.Utils;
import jpt.Timing.TypeDefs;
import jpt.Math;
import jpt.Utilities;

bool UnitTest_Clock()
{
    jpt::Timing::Point start = jpt::Timing::Now<jpt::Timing::Clock>();
    Sleep(3'000);
    jpt::Timing::Point end = jpt::Timing::Now<jpt::Timing::Clock>();

    double secondsBetween = jpt::Timing::GetSecondsBetween(start, end);
    bool value = jpt::AreValuesClose(secondsBetween, 3.0, 0.1);
    JPT_ENSURE(value);

    secondsBetween = jpt::Timing::GetSecondsFrom(start);
    value = jpt::AreValuesClose(secondsBetween, 3.0, 0.1);
    JPT_ENSURE(value);

    return true;
}

bool UnitTest_StopWatch()
{
    jpt::Timing::Point start = jpt::Timing::Now<jpt::Timing::StopWatch>();
    Sleep(3'500);
    jpt::Timing::Point end = jpt::Timing::Now<jpt::Timing::StopWatch>();

    double secondsBetween = jpt::Timing::GetSecondsBetween(start, end);
    bool value = jpt::AreValuesClose(secondsBetween, 3.5, 0.1);
    JPT_ENSURE(value);

    secondsBetween = jpt::Timing::GetSecondsFrom(start);
    value = jpt::AreValuesClose(secondsBetween, 3.5, 0.1);
    JPT_ENSURE(value);

    return true;
}

export bool RunUnitTests_Timing()
{
    JPT_ENSURE(UnitTest_Clock());
    JPT_ENSURE(UnitTest_StopWatch());

    return true;
}
