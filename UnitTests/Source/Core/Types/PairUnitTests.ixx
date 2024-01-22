// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimals/Headers.h"

export module PairUnitTests;

import jpt.CoreModules;

bool UnitTest_Pair()
{
	jpt::Pair<int, bool> pair{ 42, true };

	JPT_RETURN_FALSE_IF_ERROR(pair.first != 42, "");
	JPT_RETURN_FALSE_IF_ERROR(pair.second != true, "");

	jpt::Pair<int, bool> otherPair{ 1, false };
	pair = otherPair;
	JPT_RETURN_FALSE_IF_ERROR(pair.first != 1, "");
	JPT_RETURN_FALSE_IF_ERROR(pair.second != false, "");
	JPT_RETURN_FALSE_IF_ERROR(pair != otherPair, "");

	return true;
}

export bool RunPairUnitTests()
{
	JPT_RETURN_FALSE_IF_ERROR(!UnitTest_Pair(), "UnitTest_Pair Failed");

	return true;
}