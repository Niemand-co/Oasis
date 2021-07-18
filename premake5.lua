workspace "Oasis"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

startproject "SandBox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Inlcude directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Oasis/vendor/GLFW/include"
IncludeDir["Glad"] = "Oasis/vendor/Glad/include"
IncludeDir["ImGui"] = "Oasis/vendor/imgui"

include "Oasis/vendor/GLFW"
include "Oasis/vendor/Glad"
include "Oasis/vendor/imgui"


project "Oasis"
	location "Oasis"
	kind "SharedLib"
	language "c++"

	targetdir ( "bin/" ..outputdir.. "/%{prj.name}")
	objdir ( "bin-int/" ..outputdir.. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"OASIS_PLATFORM_WINDOWS",
			"OASIS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox")
		}

		filter "configurations:Debug"
			defines "OASIS_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "OASIS_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "OASIS_DIST"
			buildoptions "/MD"
			optimize "On"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "c++"

	targetdir ( "bin/" ..outputdir.. "/%{prj.name}")
	objdir ( "bin-int/" ..outputdir.. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"Oasis/vendor/spdlog/include",
		"Oasis/src"
	}

	links{
		"Oasis"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"OASIS_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "OASIS_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "OASIS_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "OASIS_DIST"
			buildoptions "/MD"
			optimize "On"
