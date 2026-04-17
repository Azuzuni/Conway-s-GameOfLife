#include "GameOfLife.h"
#include "screen/RaylibScreen.hpp"
#include "screen/ConsoleScreen.hpp"
#include "screen/WinApiScreen.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <windows.h>

constexpr ScreenDataType width{100};
constexpr ScreenDataType height{30};


void InitConsole();
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


// #################################################################################################
// ENTRY POINT
// #################################################################################################

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  InitConsole();

  if constexpr (backend == ScreenBackend::WinAPI) {
    GameOfLife game{ScreenData{width, height}, std::make_unique<WinApiScreen>()};
    game.Run();
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



  FreeConsole();
  return 0;
}





// #################################################################################################
// CONSOLE INIT
// #################################################################################################


// AI GENERATED
void InitConsole()
{
  AllocConsole();

  // Attach C runtime to console
  FILE* f;
  freopen_s(&f, "CONIN$",  "r", stdin);
  freopen_s(&f, "CONOUT$", "w", stdout);
  freopen_s(&f, "CONOUT$", "w", stderr);

  // IMPORTANT: also attach C++ streams properly
  std::cin.clear();
  std::cout.clear();
  std::cerr.clear();

  // Tie streams like normal console apps
  std::ios::sync_with_stdio(true);
  std::cin.tie(&std::cout);

  // Set console modes like default terminal
  HANDLE hIn  = GetStdHandle(STD_INPUT_HANDLE);
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  DWORD inMode = 0;
  GetConsoleMode(hIn, &inMode);
  inMode |= ENABLE_PROCESSED_INPUT;
  inMode |= ENABLE_LINE_INPUT;
  inMode |= ENABLE_ECHO_INPUT;
  SetConsoleMode(hIn, inMode);

  DWORD outMode = 0;
  GetConsoleMode(hOut, &outMode);
  SetConsoleMode(hOut, outMode);
}


