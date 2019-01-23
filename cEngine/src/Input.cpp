#include "Input.h"

namespace cEngine {

	Input::Input()
	{
	}

	Input::Input(const Input&) {

	}

	Input::~Input()
	{
	}

	void Input::Init() {
		int i;

		for (i = 0; i < 256; i++) {
			m_keys[i] = false;
		}

		return;
	}

	void Input::Shutdown() {
		return;
	}

	void Input::KeyDown(unsigned int input) {
		m_keys[input] = true;
		return;
	}

	void Input::KeyUp(unsigned int input) {
		m_keys[input] = false;
		return;
	}

	bool Input::IsKeyDown(unsigned int input) {
		return m_keys[input];
	}

}
