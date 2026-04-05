#ifdef _WIN32
#include "Controls.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

namespace {
  HANDLE m_cHandler{};
  HWND m_console{};
}

void Controls::Init() {
 m_cHandler = GetStdHandle(STD_OUTPUT_HANDLE); 

  if (m_cHandler == INVALID_HANDLE_VALUE || m_cHandler == nullptr) {
    std::cerr << "Error: Unable to get console handle.\n";
    return;
  }

  DWORD mode;
  if (!GetConsoleMode(m_cHandler, &mode)) {
    std::cerr << "Error: Unable to get console mode.\n";
    return;
  }

  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  if (!SetConsoleMode(m_cHandler, mode)) {
    std::cerr << "Error: Unable to enable ANSI mode.\n";
    return;
  }

  m_console = GetConsoleWindow();
} 
void Controls::Restore() {} // windows has no need for this implementation

char Controls::GetInput() {
  if (_kbhit()) return _getch();
  return 0;
}


#endif // _WIN32
