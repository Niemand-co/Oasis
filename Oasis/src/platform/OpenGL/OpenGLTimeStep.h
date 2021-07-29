#pragma once
#include "Oasis/Core/TimeStep.h"

namespace Oasis {

	class OpenGLTimeStep : public TimeStep {

	public:

		OpenGLTimeStep(float time = 0.0) : m_Time(time) {}

		virtual float UpdateTimeStep() override;

		virtual float GetSeconds() const override;
		virtual float GetMillionSeconds() const override;

	private:

		float m_Time;

	};

}