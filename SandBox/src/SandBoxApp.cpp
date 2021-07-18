#include <Oasis.h>

class ExampleLayer : public Oasis::Layer {

public:
	
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override {
		OASIS_INFO("ExampleLayer:Update");
	}

	void OnEvent(Oasis::Event& e) override {
		OASIS_TRACE("{0}", e);
	}

};


class SandBox : public Oasis::Application {

public:
	SandBox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Oasis::ImGuiLayer());
	}

	~SandBox() {

	}

};

Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}