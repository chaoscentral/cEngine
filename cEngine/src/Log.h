#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace cEngine {
	class CENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define CE_CORE_ERROR(...) ::cEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CE_CORE_WARN(...) ::cEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CE_CORE_TRACE(...) ::cEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CE_CORE_INFO(...) ::cEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CE_CORE_FATAL(...) ::cEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CE_ERROR(...) ::cEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CE_WARN(...) ::cEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CE_TRACE(...) ::cEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CE_INFO(...) ::cEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CE_FATAL(...) ::cEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

