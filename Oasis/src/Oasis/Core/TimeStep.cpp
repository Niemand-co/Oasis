#include "OApch.h"
#include "TimeStep.h"
#include "platform/OpenGL/OpenGLTimeStep.h"

namespace Oasis {

	TimeStep* TimeStep::Create() {

		return new OpenGLTimeStep();

	}

}