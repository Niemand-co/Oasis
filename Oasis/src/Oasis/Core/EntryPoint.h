#pragma once

#ifdef OASIS_PLATFORM_WINDOWS

	extern Oasis::Application* Oasis::CreateApplication();


	int main(int argc, char** argv) {
		Oasis::Log::Init();
		OASIS_CORE_WARN("Initialized Log!");
		int a = 5;
		OASIS_INFO("Hello! Var = {0}", a);


		printf("Welcome To Oasis\n");
		auto app = Oasis::CreateApplication();
		app->Run();
		delete app;
	}

#endif