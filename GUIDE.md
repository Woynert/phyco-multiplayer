# Gd extension setup

# Links

- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html

# Requirements

- a Godot 4 executable,
- a C++ compiler,
- SCons as a build tool,
- a copy of the [godot-cpp repository](https://github.com/godotengine/godot-cpp).
- [Bear](https://github.com/rizsotto/Bear) (For clangd autocompletion)

# Procedure

Start as a git repo

```
mkdir gdextension_cpp_example
cd gdextension_cpp_example
git init
git submodule add -b 4.0 https://github.com/godotengine/godot-cpp
cd godot-cpp
git submodule update --init
```

Structure

```
gdextension_cpp_example/
|
+--demo/                  # game example/demo to test the extension
|
+--godot-cpp/             # C++ bindings
|
+--src/                   # source code of the extension we are building
```

---

## Bindings

Dump bindings from your godot binary

```
cd godot-cpp
godot4 --dump-extension-api extension_api.json
```

Compile bindings

```
cd godot-cpp
scons platform=<platform> -j4 custom_api_file=<PATH_TO_FILE>
```

## Clangd autocompletion

Make sure to remove all previously compiled binaries from the bindings (godot-cpp) directory.

```
\rm -rf godot-cpp/bin
```

Wrap the **godot cpp binding** compile process into the bear tool

```
cd godot-cpp
bear -- scons platform=<platform> -j4 custom_api_file=<PATH_TO_FILE>
```

Now move the new created file `compile_commands.json` to the src directory

```
mv compile_commands.json ../src/.
```

---

## Plugin

Create a simple plugin and bind it
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#creating-a-simple-plugin

## Compile

Get the **SConstruct** file from the link below, and place it in the project root.
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#compiling-the-plugin

Compile the plugin

```
scons platform=linux
```

## Add to godot project

Create the gdextension file
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#using-the-gdextension-module

# Final structure

```
gdextension_cpp_example/
|
+--demo/                  # game example/demo to test the extension
|   +--main.tscn
|   +--bin/
|       +--gdexample.gdextension
|
+--godot-cpp/             # C++ bindings
|   ...
|   +--extension_api.json
|
+--src/                   # source code of the extension we are building
|   +--register_types.cpp
|   +--register_types.h
|   +--gdexample.cpp
|   +--gdexample.h
|   +--compile_commands.json
|
+--SConstruct
```





