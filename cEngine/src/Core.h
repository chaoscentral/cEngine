#pragma once

//On Windows setup our declspec functions to export and import appropriately based on build options
#ifdef CE_PLATFORM_WINDOWS
	#ifdef CE_BUILD_DLL
		#define CENGINE_API __declspec(dllexport)
	#else
		#define CENGINE_API __declspec(dllimport)
	#endif
#else
	//Not supported yet. Eventually we can remove this bit and add proper support for other platforms
	#error CEngine only supports Windows!
#endif
