workspace "template"
	configurations { "debug", "release" }

project "template"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files { "src/**.hpp", "src/**.cpp" }

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "On"
