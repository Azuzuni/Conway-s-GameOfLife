#include "screen/RaylibScreen.hpp"
#include "raylib.h"
#include "screen/Data.hpp"
#include <cstddef>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>

constexpr double cellPercentageX{0.5 * 0.2};
constexpr double cellPercentageY{0.5};
RaylibScreen::~RaylibScreen() { CloseWindow(); }

void RaylibScreen::Init(const std::string &fileName, ScreenData &data) {
  std::ifstream file{fileName};
  if (!file.is_open())
    throw std::runtime_error("Failed to open template.");

  std::string line{};
  for (size_t row{}; std::getline(file, line) && row < data.height; ++row) {
    for (size_t col{}; col < line.size() && col < data.width; ++col) {
      if (line[col] == '#')
        data.buff[row * data.width + col] = true;
      else
        data.buff[row * data.width + col] = false;
    }
  }
  file.close();
  cellWidth = static_cast<int>(data.width * cellPercentageX);
  cellHeight = static_cast<int>(data.height * cellPercentageY);
  if (cellWidth < 1)
    cellWidth = 1;
  if (cellHeight < 1)
    cellHeight = 1;
  int screenWidth = data.width * cellWidth;
  int screenHeight = data.height * cellHeight;

  InitWindow(screenWidth, screenHeight, "Conway's Game Of Life");
  SetTargetFPS(15);

  Draw(data);
}

bool RaylibScreen::IsOpen() { return !WindowShouldClose(); }

inline std::pair<float, float> RaylibScreen::ScreenCellPosition() {
  Vector2 mouse = GetMousePosition();

  float x = mouse.x / cellWidth;
  float y = mouse.y / cellHeight;

  return {x, y};
}

void RaylibScreen::Compute(ScreenData &data) {
  if (IsKeyPressed(KEY_P))
    data.isPaused = !data.isPaused;
  if (!data.isPaused)
    return;

  std::pair<float, float> mouse = ScreenCellPosition();
  int x = static_cast<int>(mouse.first);
  int y = static_cast<int>(mouse.second);

  if (x >= data.width || y >= data.height)
    return;
  if (x < 0 || y < 0)
    return;

  if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    return;

  data.buff[y * data.width + x] = !data.buff[y * data.width + x];
}

void RaylibScreen::Draw(ScreenData &data) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  for (ScreenDataType row{}; row < data.height; ++row) {
    for (ScreenDataType col{}; col < data.width; ++col) {

      int x = col * cellWidth;
      int y = row * cellHeight;

      Color color = data.buff[row * data.width + col] ? WHITE : BLACK;
      DrawRectangle(x, y, cellWidth, cellHeight, color);
    }
  }

  std::pair<float, float> mouse = ScreenCellPosition();
  int x = static_cast<int>(mouse.first);
  int y = static_cast<int>(mouse.second);
  DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight,
                Color{GRAY});

  size_t count = std::accumulate(data.buff.begin(), data.buff.end(), 0);
  DrawText(std::to_string(count).c_str(), 0, 0, cellHeight * 2, RED);
  EndDrawing();
}
