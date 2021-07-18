#include "ImGuiLayer.h"

#include "imgui.h"
#include "platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Oasis/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()	{
	}

	void ImGuiLayer::OnUpdate() {

        ImGuiIO& io = ImGui::GetIO();

        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float CurrentTime = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (CurrentTime - m_Time) : (1.0f / 60.0f);
        m_Time = CurrentTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& event) {

        EventDispatcher dispathcer(event);
        dispathcer.DispatchEvent<MouseButtonPressedEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiMouseButtonPressedEvent));
        dispathcer.DispatchEvent<MouseButtonReleasedEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiMouseButtonReleasedEvent));
        dispathcer.DispatchEvent<MouseMoveEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiMouseMovedEvent));
        dispathcer.DispatchEvent<MouseScrollEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiMouseScrolledEvent));
        dispathcer.DispatchEvent<WindowResizeEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiWindowResizedEvent));
        dispathcer.DispatchEvent<KeyPressedEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiKeyPressedEvent));
        dispathcer.DispatchEvent<KeyReleasedEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiKeyReleasedEvent));
        dispathcer.DispatchEvent<KeyTypeEvent>(OASIS_BIND_EVENT_FUNC(ImGuiLayer::ImGuiKeyTypeEvent));

	}

    bool ImGuiLayer::ImGuiMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }
    
    bool ImGuiLayer::ImGuiMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::ImGuiMouseMovedEvent(MouseMoveEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetPosX(), e.GetPosY());

        return false;
    }

    bool ImGuiLayer::ImGuiMouseScrolledEvent(MouseScrollEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetOffsetX();
        io.MouseWheel += e.GetOffsetY();

        return false;
    }

    bool ImGuiLayer::ImGuiWindowResizedEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWindowWidth(), e.GetWindowHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWindowWidth(), e.GetWindowHeight());

        return false;
    }

    bool ImGuiLayer::ImGuiKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::ImGuiKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::ImGuiKeyTypeEvent(KeyTypeEvent& e) {

        ImGuiIO& io = ImGui::GetIO();
        int KeyCode = e.GetKeyCode();
        if (KeyCode > 0 && KeyCode < 0x10000) {
            io.AddInputCharacter((unsigned short)KeyCode);
        }

        return false;

    }

}