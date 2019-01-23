#pragma once

#ifndef _INPUT_H_
#define _INPUT_H_

namespace cEngine {
	class Input
	{
	public:
		Input();
		Input(const Input&);
		~Input();

		void Init();
		void Shutdown();

		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);
	private:
		bool m_keys[256];
	};
}

#endif