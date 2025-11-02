# Building the Project

Below are the step-by-step instructions for cloning, configuring, building, and running the Raylib + ImGui scaffold using CMake. This section is perfect for including in your README.

---

## Prerequisites

* **CMake 3.21+**
* **A C++20 compiler**  (MSVC, MinGW-w64, Clang, or GCC)
* **Git** (for FetchContent)
* **Raylib dependencies** (OpenGL, GLFW, etc. are fetched automatically)
* *(Optional)* **ccache** for faster rebuilds

---

## 1️⃣ Clone the repository

```bash
git clone https://github.com/yourusername/rayproj.git
cd rayproj
```

---

## 2️⃣ Configure the project with CMake presets

### Debug configuration

```bash
cmake --preset debug
```

### Release configuration

```bash
cmake --preset release
```

> The first run will automatically fetch and build **Raylib**, **Dear ImGui**, and **rlImGui** from GitHub.

---

## 3️⃣ Build the project

### Linux & macOS

```bash
cmake --build --preset debug -j
```

### Windows (MinGW or MSVC)

```powershell
cmake --build --preset debug -j
```

This will compile the project and place the executable inside the **bin/** directory.

---

## 4️⃣ Run the executable

### Linux & macOS

```bash
./bin/rayproj
```

### Windows

```powershell
./bin/rayproj.exe
```

You should see a window titled **“rayproj | Shaders + ImGui”** with a moving texture, a color tint controlled by ImGui, and an FPS counter.

---

## 5️⃣ Verify ImGui integration

If ImGui is working, you will see:

* A small **“Controls”** window with sliders and color pickers.
* An optional **Demo Window** (toggle via checkbox).

If you only see a blank screen, ensure:

* The `rlImGuiBegin()` / `rlImGuiEnd()` calls are wrapped inside `BeginDrawing()` / `EndDrawing()`.
* The `imgui` and `rlimgui` targets are linked in **CMakeLists.txt**.
* You restarted Neovim so clangd reindexed the `compile_commands.json`.

---

## 6️⃣ Cleaning and rebuilding

If you need to reconfigure everything from scratch:

```bash
rm -rf build/
cmake --preset debug
cmake --build --preset debug -j
```

On Windows:

```powershell
Remove-Item -Recurse -Force build
cmake --preset debug
cmake --build --preset debug -j
```

---

## 7️⃣ Optional development notes

* Neovim + clangd support is already configured via `.clangd` and `compile_commands.json`.
* Assets and shaders are copied automatically to the `bin/` directory after each build.
* You can modify `CMakePresets.json` to customize compiler options or output directories.

---
