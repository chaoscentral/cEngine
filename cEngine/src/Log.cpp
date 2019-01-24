#include "Log.h"

namespace cEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//Set the pattern for spdlog
		spdlog::set_pattern("%^[%T] %n: %v%$");
		//Initialize our CoreLogger and set it's name to CENGINE with a level of trace
		s_CoreLogger = spdlog::stdout_color_mt("CENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		//Initialize our ClientLogger and set it's name to APP with a level of trace
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
