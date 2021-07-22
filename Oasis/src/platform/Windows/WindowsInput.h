#pragma once

#include "Oasis/Input.h"

namespace Oasis {

	class WindowsInput : public Input {

	protected:
		virtual bool IsKeyPressedImp(int keycode) override;
		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual float GetMousePosXImp() override;
		virtual float GetMousePosYImp() override;
		virtual std::pair<float, float> GetMousePosImp() override;

	};

}