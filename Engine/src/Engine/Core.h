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
