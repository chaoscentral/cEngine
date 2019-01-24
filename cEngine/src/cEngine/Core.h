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

#ifdef CE_ENABLE_ASSERTS
	#define CE_ASSERT(x, ...) { if(!(x)) { CE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CE_CORE_ASSERT(x, ...) { if(!(x)) { CE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CE_ASSERT(x, ...)
	#define CE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)