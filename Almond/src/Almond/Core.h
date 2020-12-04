#pragma once

#ifdef AL_PLATFORM_WINDOWS
	#ifdef AL_BUILD_DLL
		#define ALMOND_API __declspec(dllexport)
	#else 
		#define ALMOND_API __declspec(dllimport)
	#endif
#else
	#error Almond is windows only
#endif // 
