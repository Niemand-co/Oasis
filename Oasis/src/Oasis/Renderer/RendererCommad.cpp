#include "OApch.h"
#include "RendererCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace Oasis {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;

}