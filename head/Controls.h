#pragma once
#include "screen/Data.hpp"
#include <cstddef>
#include <utility>

class Controls {
  Controls() = delete;
  Controls(Controls &&) = delete;
  Controls(const Controls &) = delete;
  Controls &operator=(Controls &&) = delete;
  Controls &operator=(const Controls &) = delete;
  ~Controls() = delete;

  static bool canControl;
  static size_t posX;
  static size_t posY;
  static char GetInput();

public:
  static void Init();
  static void Restore();
  static bool HandleControl(ScreenData&);
  static void MoveCursor(size_t, size_t);
  static std::pair<size_t, size_t> GetPosition() { return {posX, posY}; }
};
