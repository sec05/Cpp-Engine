#pragma once
#ifdef ES_PLATFORM_WINDOWS
	#ifdef ES_BUILD_DLL //checks if the dll is being imported or exported
		#define ES_API _declspec(dllexport)
	#else 
		#define ES_API _declspec(dllimport)
	#endif 
#else
	#error	Engine only supports windows
#endif 

#ifdef ES_ENABLE_ASSERTS
#define ES_ASSERT(x,...){if(!(x)){ES_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#define ES_CORE_ASSERT(x,...){if(!(x)){ES_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#else
#define ES_ASSERT(x,...)
#define ES_CORE_ASSERT(x,...)
#endif // ES_ENABLE_ASSERTS

#define BIT(x) (1<<x) //creates a bitfield 