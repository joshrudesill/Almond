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
IncludeDir["Glad"] = "Almond/vendor/Glad/include"
IncludeDir["ImGui"] = "Almond/vendor/imgui"

include "Almond/vendor/GLFW"
include "Almond/vendor/Glad"
include "Almond/vendor/imgui"

project "Almond"
	location "Almond"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
	
		systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS",
			"AL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "AL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "AL_DIST"
		runtime "Release"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		staticruntime "off"
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
			
			systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS"
			
		}



		filter "configurations:Debug"
			defines "AL_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "AL_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "AL_DIST"
			runtime "Release"
			optimize "On"