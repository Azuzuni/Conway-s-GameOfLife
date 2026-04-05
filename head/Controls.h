#pragma once
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
  static void Init();    // store old console settings and initialize new behaviour (unix), on windows its empty
  static void Restore(); // restore old console behaviour (unix), on windows its empty
  static bool HandleControl();
  static void MoveCursor(size_t, size_t);
  static std::pair<size_t, size_t> GetPosition() {return {posX,posY};}
};
