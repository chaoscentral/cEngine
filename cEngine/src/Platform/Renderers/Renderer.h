#pragma once

namespace cEngine {
	class CENGINE_API Renderer {
	public:
		virtual int Init() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
	};
}