#pragma once
#ifdef ES_PLATFORM_WINDOWS
	#ifdef ES_BUILD_DLL
		#define ES_API _declspec(dllexport)
	#else 
		#define ES_API _declspec(dllimport)
	#endif 
#else
	#error	Engine only supports windows
#endif 
