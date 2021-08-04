#pragma once
#include "Oasis/Core/Core.h"

namespace Oasis {

	class OASIS_API TimeStep {

	public:

		static TimeStep* Create();

		virtual float UpdateTimeStep() = 0;

		virtual float GetSeconds() const = 0;
		virtual float GetMillionSeconds() const = 0;

	};

}