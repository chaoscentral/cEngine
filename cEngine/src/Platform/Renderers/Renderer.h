#pragma once

#include "cEngine/Events/Event.h"

namespace cEngine {
	class CENGINE_API Renderer {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual int Init() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() = 0;
	};
}