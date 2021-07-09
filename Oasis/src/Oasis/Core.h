#pragma once

#ifdef OASIS_PLATFORM_WINDOWS
	#ifdef OASIS_BUILD_DLL
		#define OASIS_API __declspec(dllexport)
	#else
		#define OASIS_API __declspec(dllimport)
	#endif
#else
	#error OASIS ONLY SUPPORT WINDOWS!
#endif // OASIS_PLATFORM_WINDOWS
