#include "OApch.h"
#include "OpenGLTimeStep.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Oasis {

    float OpenGLTimeStep::UpdateTimeStep() {

        float CurrentTime = glfwGetTime();
        float DeltaTime = CurrentTime - m_Time;
        m_Time = CurrentTime;
        return DeltaTime;

    }

    float OpenGLTimeStep::GetSeconds() const{
        return m_Time;
    }

    float OpenGLTimeStep::GetMillionSeconds() const{
        return m_Time * 1000.0f;
    }

}
