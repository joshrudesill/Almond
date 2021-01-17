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
IncludeDir["glm"] = "Almond/vendor/glm"

include "Almond/vendor/GLFW"
include "Almond/vendor/Glad"
include "Almond/vendor/imgui"

project "Almond"
	location "Almond"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Almond/src/hzpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"


	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"


	}
	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		
	
		systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS",
			"AL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		

	filter "configurations:Debug"
		defines "AL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AL_DIST"
		runtime "Release"
		optimize "on"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
		

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
		"Almond/src",
		"Almond/vendor",
		"%{IncludeDir.glm}",
		}

		links
		{
			"Almond"
		}

		filter "system:windows"
			systemversion "latest"

		defines 
		{
			"AL_PLATFORM_WINDOWS",
			
		}



		filter "configurations:Debug"
			defines "AL_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "AL_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "AL_DIST"
			runtime "Release"
			optimize "on"