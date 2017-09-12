-- Make gmake the default action
if not _ACTION then
        _ACTION = "gmake"
end

workspace "Tests"
        configurations { "Debug", "Release" }

project "app"
        kind "ConsoleApp"
        language "C++"

        includedirs { "." }
        files { "*.hpp", "*.cpp" }

        filter "configurations:Debug"
                defines { "_DEBUG" }
                symbols "On"
                links { "sfml-system", "sfml-window", "sfml-graphics" }

        filter "configurations:Release"
                defines { "_RELEASE" }
                symbols "Off"
                links { "sfml-system", "sfml-window", "sfml-graphics" }

-- Removes all generated and compiled files
newaction {
        trigger = "clean",
        description = "Clean the software.",
        execute = function ()
                os.rmdir("./build")
                os.rmdir("./bin")
                os.rmdir("./obj")
                os.remove("./Makefile")
                os.remove("./*.make")
                print("Done.")
        end
}
