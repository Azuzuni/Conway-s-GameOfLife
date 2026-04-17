#pragma once
#include <cstdint>
#include <vector>

typedef uint16_t ScreenDataType;

struct ScreenData {
  ScreenDataType width{};
  ScreenDataType height{};
  std::vector<uint8_t> buff;
  bool isPaused{true};
  ScreenData(ScreenDataType width, ScreenDataType height)
      : width(width), height(height), buff(width * height, 0) {}
};
