#include "GameOfLife.h"
#include "screen/ConsoleScreen.hpp"
#include "screen/Data.hpp"
#include "screen/RaylibScreen.hpp"
#include <cassert>
#include <memory>

constexpr ScreenDataType width{100};
constexpr ScreenDataType height{30};

enum class ScreenBackend {
  WinAPI = 0,
  Raylib = 1,
  ConsoleColors = 2,
  ConsoleText = 3
};


#ifdef SCREEN_BACKEND

#if SCREEN_BACKEND == 0
constexpr ScreenBackend backend = ScreenBackend::WinAPI;
#elif SCREEN_BACKEND == 1
constexpr ScreenBackend backend = ScreenBackend::Raylib;
#elif SCREEN_BACKEND == 2
constexpr ScreenBackend backend = ScreenBackend::ConsoleColors;
#elif SCREEN_BACKEND == 3
constexpr ScreenBackend backend = ScreenBackend::ConsoleText;
#else
#error "Invalid SCREEN_BACKEND"
#endif
#endif

int main() {
  
  if constexpr (backend == ScreenBackend::WinAPI) {
    assert(false && "WinAPI is not supported on unix systems");
  }
  else if constexpr (backend == ScreenBackend::Raylib) {
    GameOfLife game{ScreenData{width, height}, std::make_unique<RaylibScreen>()};
    game.Run();
  }
  else if constexpr (backend == ScreenBackend::ConsoleColors) {
    GameOfLife game{ScreenData{width, height}, std::make_unique<ConsoleScreen<true>>()};
    game.Run();
  }
  else if constexpr (backend == ScreenBackend::ConsoleText) {
    GameOfLife game{ScreenData{width, height}, std::make_unique<ConsoleScreen<false>>()};
    game.Run();
  }
  else assert(false && "Incorrect Backend\n");

  return 0;
}
