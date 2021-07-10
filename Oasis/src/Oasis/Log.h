#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace Oasis {
	class OASIS_API Log{

	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};
}

#define OASIS_CORE_ERROR(...) ::Oasis::Log::GetCoreLogger()->error(__VA_ARGS__);
#define OASIS_CORE_WARN(...) ::Oasis::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define OASIS_CORE_TRACE(...) ::Oasis::Log::GetCoreLogger()->info(__VA_ARGS__);
#define OASIS_CORE_INFO(...) ::Oasis::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define OASIS_CORE_FATAL(...) ::Oasis::Log::GetCoreLogger()->fatal(__VA_ARGS__);


#define OASIS_ERROR(...) ::Oasis::Log::GetClientLogger()->error(__VA_ARGS__);
#define OASIS_WARN(...) ::Oasis::Log::GetClientLogger()->warn(__VA_ARGS__);
#define OASIS_TRACE(...) ::Oasis::Log::GetClientLogger()->info(__VA_ARGS__);
#define OASIS_INFO(...) ::Oasis::Log::GetClientLogger()->trace(__VA_ARGS__);
#define OASIS_FATAL(...) ::Oasis::Log::GetClientLogger()->fatal(__VA_ARGS__);