// Copyright Jupiter Technologies, Inc. All Rights Reserved.

import jpt.EntryPoints;

/** Main entry point for different platforms */
#if IS_PLATFORM_WIN64

#include <Windows.h>

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lPStr, int nCmdShow)
{
	return jpt::MainImpl_Win64(hInstance, hPrevInstance, lPStr, nCmdShow);
}
#endif
