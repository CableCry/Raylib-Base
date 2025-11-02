#include "raylib.h"
#include "rlgl.h"
#include "rlImGui.h"
#include <imgui.h>

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(1280, 720, "rayproj | Shaders + ImGui");
  SetTargetFPS(60);

  rlImGuiSetup(true);

  Texture2D tex = LoadTexture("assets/textures/placeholder.png");
  if (tex.id == 0) {
    Image img = GenImageColor(128, 128, DARKPURPLE);
    tex = LoadTextureFromImage(img);
    UnloadImage(img);
  }
  Shader sh = LoadShader("shaders/basic.vs", "shaders/basic.fs");

  const int uTimeLoc = GetShaderLocation(sh, "u_time");
  const int colTint  = GetShaderLocation(sh, "colTint");

  float tint[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  SetShaderValue(sh, colTint, tint, SHADER_UNIFORM_VEC4);

  bool show_demo = true;
  float clear[4] = {0.10f, 0.12f, 0.15f, 1.0f};
  float timeAcc = 0.0f;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    timeAcc += dt;

    BeginDrawing();
    ClearBackground(Color{
      (unsigned char)(clear[0] * 255.0f),
      (unsigned char)(clear[1] * 255.0f),
      (unsigned char)(clear[2] * 255.0f),
      (unsigned char)(clear[3] * 255.0f)
    });


    BeginShaderMode(sh);
    SetShaderValue(sh, uTimeLoc, &timeAcc, SHADER_UNIFORM_FLOAT);

    const float cx = static_cast<float>(GetScreenWidth())  * 0.5f - static_cast<float>(tex.width)  * 0.5f;
    const float cy = static_cast<float>(GetScreenHeight()) * 0.5f - static_cast<float>(tex.height) * 0.5f;
    DrawTexture(tex, (int)cx, (int)cy, WHITE);

    EndShaderMode();

    DrawText("Raylib + GLSL + ImGui (rlImGui) + CMake", 24, 24, 20, RAYWHITE);

    rlImGuiBegin();
    if (ImGui::Begin("Controls")) {
      ImGui::Checkbox("Show Demo Window", &show_demo);
      ImGui::ColorEdit3("Clear Color", clear);                 // edit window clear color
      if (ImGui::ColorEdit4("Tint (shader colTint)", tint)) {  // push to shader when changed
        SetShaderValue(sh, colTint, tint, SHADER_UNIFORM_VEC4);
      }
      ImGui::Text("FPS: %d", GetFPS());
    }
    ImGui::End();
    if (show_demo) ImGui::ShowDemoWindow(&show_demo);
    rlImGuiEnd();

    EndDrawing();
  }

  UnloadShader(sh);
  UnloadTexture(tex);
  rlImGuiShutdown();
  CloseWindow();
  return 0;
}

