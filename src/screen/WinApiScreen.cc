#ifdef WIN32

#include "screen/WinApiScreen.h"
#include "screen/Data.hpp"
#include <fstream>
#include <string>
#include <windows.h>

constexpr double cellPercentageX{0.5 * 0.2};
constexpr double cellPercentageY{0.5};
static inline void LoadTemplate(const std::string &fileName, ScreenData &data,
                                int &cellWidth, int &cellHeight) {
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
}

static inline void DrawCells(HWND hwnd, ScreenData &data, int cellWidth,
                             int cellHeight) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
  HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));

  for (ScreenDataType row = 0; row < data.height; ++row) {
    for (ScreenDataType col = 0; col < data.width; ++col) {

      int x = col * cellWidth;
      int y = row * cellHeight;

      RECT rect;
      rect.left = x;
      rect.top = y;
      rect.right = x + cellWidth;
      rect.bottom = y + cellHeight;

      HBRUSH brush = data.buff[row * data.width + col] ? white : black;

      FillRect(hdc, &rect, brush);
    }
  }

  DeleteObject(white);
  DeleteObject(black);

  EndPaint(hwnd, &ps);
}

// BEYOND THIS POOINT EVERYTHING ENTIRELY AI GENERATED

// --------------------
// Constructor / Destructor
// --------------------

WinApiScreen::~WinApiScreen() {
  if (hwnd) {
    DestroyWindow(hwnd);
    hwnd = nullptr;
  }
}

// --------------------
// Window Procedure
// --------------------

LRESULT CALLBACK WinApiScreen::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                       LPARAM lParam) {
  WinApiScreen *self = nullptr;

  if (msg == WM_NCCREATE) {
    CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT *>(lParam);
    self = reinterpret_cast<WinApiScreen *>(cs->lpCreateParams);

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);

    SetWindowLongPtr(hwnd, GWLP_USERDATA + sizeof(LONG_PTR),
                     (LONG_PTR)cs->lpCreateParams);
  } else {
    self =
        reinterpret_cast<WinApiScreen *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
  }

  if (self) {
    switch (msg) {
    case WM_PAINT: {
      WinApiScreen *self = reinterpret_cast<WinApiScreen *>(
          GetWindowLongPtr(hwnd, GWLP_USERDATA));

      if (!self || !self->dataRef)
        return 0;

      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      auto &data = *self->dataRef;

      HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
      HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));

      for (ScreenDataType row = 0; row < data.height; ++row) {
        for (ScreenDataType col = 0; col < data.width; ++col) {

          RECT rect;
          rect.left = col * self->cellWidth;
          rect.top = row * self->cellHeight;
          rect.right = rect.left + self->cellWidth;
          rect.bottom = rect.top + self->cellHeight;

          HBRUSH brush = data.buff[row * data.width + col] ? black : white;

          FillRect(hdc, &rect, brush);
        }
      }

      DeleteObject(white);
      DeleteObject(black);

      EndPaint(hwnd, &ps);
      return 0;
    }

    case WM_CLOSE:
      self->isOpen = false;
      DestroyWindow(hwnd);
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}

// --------------------
// Interface Implementation
// --------------------

void WinApiScreen::Init(const std::string &title, ScreenData &data) {
  ::LoadTemplate(title, data, cellWidth, cellHeight);
  hInstance = GetModuleHandle(nullptr);
  dataRef = &data;

  const char *className = "MinimalWinApiWindow";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = className;

  RegisterClass(&wc);

  hwnd = CreateWindowEx(0, className, title.c_str(), WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr,
                        nullptr, hInstance, this);

  ShowWindow(hwnd, SW_SHOW);
  isOpen = true;
}

bool WinApiScreen::IsOpen() { return isOpen; }

void WinApiScreen::Compute(ScreenData &data) {
  data.isPaused = false;
  MSG msg;

  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      isOpen = false;
      break;
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
void WinApiScreen::Draw(ScreenData &) {
  if (!hwnd)
    return;

  InvalidateRect(hwnd, nullptr, FALSE); // request repaint
  UpdateWindow(hwnd);                   // force immediate WM_PAINT
}
#endif
