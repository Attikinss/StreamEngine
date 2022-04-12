workspace "StreamEngine"
    architecture "x64"
    startproject "Game"

    configurations {
        "Debug",
        "Release"
    }

output_directory = "%{cfg.buildcfg}"

ThirdParty = {}
ThirdParty["Box2D"] = "Engine/ThirdParty/Box2D"
ThirdParty["ENTT"] = "Engine/ThirdParty/ENTT"
ThirdParty["GLFW"] = "Engine/ThirdParty/GLFW"
ThirdParty["GLAD"] = "Engine/ThirdParty/GLAD"
ThirdParty["GLM"] = "Engine/ThirdParty/GLM"
ThirdParty["Spdlog"] = "Engine/ThirdParty/Spdlog"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. output_directory .. "/%{prj.name}")
    objdir ("bin-int/" .. output_directory .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source",
        "Engine/Source",

        -- Third Party
        "%{ThirdParty.ENTT}",
        "%{ThirdParty.GLFW}",
        "%{ThirdParty.GLM}",
        "%{ThirdParty.Spdlog}/include"
    }

    links {
        "Engine"
    }

    filter "system.windows"
        systemversion "latest"

    filter "configurations.Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations.Release"
        runtime "Release"
        optimize "on"

project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    pchheader "StreamEnginePCH.h"
    pchsource "%{prj.name}/Source/StreamEnginePCH.cpp"
    
    targetdir ("bin/" .. output_directory .. "/%{prj.name}")
    objdir ("bin-int/" .. output_directory .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs {
        "%{prj.name}/Source",
        
        -- Third Party
        "%{ThirdParty.Box2D}/include",
        "%{ThirdParty.ENTT}",
        "%{ThirdParty.GLAD}/include",
        "%{ThirdParty.GLFW}/include",
        "%{ThirdParty.GLM}",
        "%{ThirdParty.Spdlog}/include"
    }
    
    libdirs {
        "%{ThirdParty.Box2D}/lib",
        "%{ThirdParty.GLAD}/lib",
        "%{ThirdParty.GLFW}/lib"
    }

    links {
        "box2d.lib",
        "glad.lib",
        "glfw3_mt.lib",
        "opengl32.lib"
    }

    filter "system.windows"
        systemversion "latest"

    filter "configurations.Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations.Release"
        runtime "Release"
        optimize "on"