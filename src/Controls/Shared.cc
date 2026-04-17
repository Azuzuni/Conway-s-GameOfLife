#include "Controls.h"
#include "screen/Data.hpp"
#include <cstddef> // size_t
#include <iostream>

bool Controls::canControl{true};
size_t Controls::posX{};
size_t Controls::posY{};

bool Controls::HandleControl(ScreenData &data) {
  char c{Controls::GetInput()};
  if (!c)
    return canControl;

  if (c == 'p' || c == 'P') {
    canControl ^= 0x01; // toggle on and off
    data.isPaused = canControl;
  }
  if (!canControl)
    return false;
  switch (c) {
  case 'w':
  case 'W':
    if (posX < data.width && posY - 1 < data.height)
      if (posX >= 0 && posY - 1 >= 0)
        Controls::MoveCursor(posX, posY - 1);
    break;

  case 'a':
  case 'A':
    if ((posX - 1) < data.width && posY < data.height)
      if (posX - 1 >= 0 && posY >= 0)
        Controls::MoveCursor(posX - 1, posY);
    break;

  case 's':
  case 'S':
    if (posX < data.width && posY + 1 < data.height)
      if (posX >= 0 && posY + 1 >= 0)
        Controls::MoveCursor(posX, posY + 1);
    break;

  case 'd':
  case 'D':
    if ((posX + 1) < data.width && posY < data.height)
      if (posX + 1 >= 0 && posY >= 0)
        Controls::MoveCursor(posX + 1, posY);
    break;

  case ' ':
    if (!(posY < data.buff.size() && posX < data.width))
      break;
    data.buff[posY * data.width + posX] = !data.buff[posY * data.width + posX];
    return false;
    break;
  }
  return true;
}

void Controls::MoveCursor(size_t x, size_t y) {
  posX = x;
  posY = y;
  std::cout << "\x1b[" << y + 1 << ';' << x + 1 << "H";
}
