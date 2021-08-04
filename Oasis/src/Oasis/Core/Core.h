#pragma once
#include <memory>

#ifdef OASIS_PLATFORM_WINDOWS
	#ifdef OASIS_BUILD_DLL
		#define OASIS_API //__declspec(dllexport)
	#else
		#define OASIS_API //__declspec(dllimport)
		#define IMGUI_API //__declspec(dllimport)
	#endif
#else
	#error OASIS ONLY SUPPORT WINDOWS!
#endif // OASIS_PLATFORM_WINDOWS

#ifdef OASIS_ENABLE_ASSERTS
	#define OASIS_ASSERT(x, ...) if(!(x)) {OASIS_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}
	#define OASIS_CORE_ASSERT(x, ...) if(!(x)) {OASIS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}
#else
	#define OASIS_ASSERT(x, ...)
	#define OASIS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define OASIS_BIND_EVENT_FUNC(FUNC) std::bind(&FUNC, this, std::placeholders::_1)

namespace Oasis {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}