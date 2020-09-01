workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["freetype"] = "Engine/vendor/freetype/freetype-bin/include"
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/vendor/imgui"
IncludeDir["glm"] = "Engine/vendor/glm"
IncludeDir["stb_image"] = "Engine/vendor/stb_image"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/imgui"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "espch.h"
	pchsource "Engine/src/espch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/freetype/freetype-bin/include**.h",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		"%{IncludeDir.freetype}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
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
			"ES_PLATFORM_WINDOWS",
			"ES_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		
	filter "configurations:Debug"
		defines "ES_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ES_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ES_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src",
		"Engine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.freetype}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ES_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ES_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ES_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ES_DIST"
		runtime "Release"
		optimize "On"