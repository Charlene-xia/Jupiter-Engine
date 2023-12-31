// Copyright Jupiter Technologies, Inc. All Rights Reserved.

import jpt.EntryPoints;
import jpt.UnitTestsApplication;
import jpt.CoreModules;

/** Must Overrides Application GetInstance here */
jpt::ApplicationBase& jpt::ApplicationBase::GetInstance()
{
	static JupiterUnitTestsApplication s_instance;
	return s_instance;
}

/** Main entry point for different platforms */
#if IS_PLATFORM_WIN64

#include <Windows.h>

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lPStr, int nCmdShow)
{
	return jpt::MainImplWin64(hInstance, hPrevInstance, lPStr, nCmdShow);
}
#endif

/** Default Main Function */
int main()
{
	return jpt::MainImplWin64(nullptr, nullptr, nullptr, 0);
}
