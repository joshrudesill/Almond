workspace "Almond"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug", 
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Almond/vendor/GLFW/include"
include "Almond/vendor/GLFW"

project "Almond"
	location "Almond"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Almond/src/hzpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	links 
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS",
			"AL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AL_DIST"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"

		language "C++"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")
		files 
		{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
		"Almond/vendor/spdlog/include",
		"Almond/src"
		}

		links
		{
			"Almond"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS",
			
		}



		filter "configurations:Debug"
			defines "AL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "AL_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "AL_DIST"
			optimize "On"