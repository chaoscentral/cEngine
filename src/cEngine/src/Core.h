#pragma once

#ifdef CE_PLATFORM_WINDOWS
	#ifdef CE_BUILD_DLL
		#define CENGINE_API __declspec(dllexport)
	#else
		#define CENGINE_API __declspec(dllimport)
	#endif
#else
	#error CEngine only supports Windows!
#endif
