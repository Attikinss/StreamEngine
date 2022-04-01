workspace "StreamEngine"
    architecture "x64"
    startproject "Game"

    configurations {
        "Debug",
        "Release"
    }

output_directory = "%{cfg.buildcfg}"

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
        "Engine/Source"
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
    
    targetdir ("bin/" .. output_directory .. "/%{prj.name}")
    objdir ("bin-int/" .. output_directory .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source"
    }

    filter "system.windows"
        systemversion "latest"

    filter "configurations.Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations.Release"
        runtime "Release"
        optimize "on"