#include <Oasis.h>
#include "imgui.h"

class ExampleLayer : public Oasis::Layer {

public:
	
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override {

		if (Oasis::Input::IsKeyPressed(OASIS_KEY_SPACE))
			OASIS_TRACE("Space is pressed.");
	}

	virtual void ImGuiRender() override {
		ImGui::Begin("Tese");
		ImGui::Text("Hellow World");
		ImGui::End();
	}

	void OnEvent(Oasis::Event& e) override {

		if (e.GetEventType() == Oasis::EventType::KeyPressed) {

			Oasis::KeyPressedEvent& event = (Oasis::KeyPressedEvent&)e;
			OASIS_TRACE("{0}", (char)event.GetKeyCode());

		}

	}

};


class SandBox : public Oasis::Application {

public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}

	~SandBox() {

	}

};

Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}