#pragma once

#include "Oasis/Core.h"

namespace Oasis {

	class OASIS_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImp(keycode); }

		inline static bool MouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static float GetMousePosY() { return s_Instance->GetMousePosXImp(); }
		inline static float GetMousePosX() { return s_Instance->GetMousePosYImp(); }
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImp(); }

	protected:
		virtual bool IsKeyPressedImp(int keycode) = 0;
		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual float GetMousePosXImp() = 0;
		virtual float GetMousePosYImp() = 0;
		virtual std::pair<float, float> GetMousePosImp() = 0;

	private:
		static Input* s_Instance;

	};

}