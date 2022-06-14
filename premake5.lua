workspace "msw"
	configurations { "debug", "release" }

project "msw_test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	warnings "Extra"

	files { "tests/**.hpp", "tests/**.cpp" }

	includedirs { "include" }

	filter { "configurations:debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:release" }
		optimize "On"
