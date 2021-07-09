#pragma once

#ifdef OASIS_PLATFORM_WINDOWS

	extern Oasis::Application* Oasis::CreateApplication();


	int main(int argc, char** argv) {
		printf("Welcome To Oasis\n");
		auto app = Oasis::CreateApplication();
		app->Run();
		delete app;
	}

#endif