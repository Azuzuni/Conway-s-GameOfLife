
#pragma once

#include "screen/Data.hpp"
#include "screen/ScreenIF.hpp"
// BEYOND THIS POINT EVERYTHING ENTIRELY AI GENERATED

#include <string>
#include <windows.h>

class WinApiScreen : public ScreenIF {
private:
  HWND hwnd = nullptr;
  HINSTANCE hInstance = nullptr;
  bool isOpen = false;
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                  LPARAM lParam);
  HBRUSH blackBrush, whiteBrush;

  ScreenData* dataRef{nullptr};
  int cellWidth{};
  int cellHeight{};

public:
  WinApiScreen() = default;
  ~WinApiScreen() override;

  void Init(const std::string &title, ScreenData &) override;
  bool IsOpen() override;
  void Compute(ScreenData &) override;
  void Draw(ScreenData &) override;
};
