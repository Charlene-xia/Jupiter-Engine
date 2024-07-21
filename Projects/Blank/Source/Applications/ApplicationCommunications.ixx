// This file overrides the global communication functions through out both engine and client

module;

#include "Application_Blank.h"

export module ApplicationCommunications;

import jpt.File.Path;

/** Must Overrides Application GetInstance here */
jpt::Application_Base* jpt::Application_Base::GetInstance()
{
	static Application_Blank s_instance;
	return &s_instance;
}

/** Must Overrides GetClientDir here */
const char* jpt::GetClientDir()
{
	return JPT_CLIENT_DIR;
}
const wchar_t* jpt::GetClientDirW()
{
	return JPT_CLIENT_DIR_W;
}
