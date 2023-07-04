#!/usr/bin/env python
import os
import sys
import SCons

gameDirectory = "PhycoServer"
env = SConscript("godot-cpp/SConstruct")

def GlobRecursive(pattern, node='.'):
    results = []
    for f in Glob(str(node) + '/*', source=True):
        if type(f) is SCons.Node.FS.Dir:
            results += GlobRecursive(pattern, f)
    results += Glob(str(node) + '/' + pattern, source=True)
    return results

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = GlobRecursive("*.cpp", "src/")
# sources += (GlobRecursive("*.hpp", "src/"))

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
            gameDirectory, env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/bin/libgdexample{}{}".format(gameDirectory, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
