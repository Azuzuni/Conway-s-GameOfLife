#include "Controls.h"
#include "Screen.h"
#include <cstddef> // size_t
#include <iostream>

bool Controls::canControl{true};
size_t Controls::posX{};
size_t Controls::posY{};


bool Controls::HandleControl() {
  char c{Controls::GetInput()};
  if(!c) return canControl;

  if(c == 'p' || c =='P') canControl ^= 0x01; // toggle on and off
  if(!canControl) return false;
  switch(c) {
    case 'w':
    case 'W': 
      if(Screen::IsWithinBounds(posX, posY-1))
      Controls::MoveCursor(posX, posY-1); break;

    case 'a':
    case 'A': 
      if(Screen::IsWithinBounds(posX-1, posY)) 
      Controls::MoveCursor(posX-1, posY); break;

    case 's':
    case 'S': 
      if(Screen::IsWithinBounds(posX, posY+1))
      Controls::MoveCursor(posX, posY+1); break;

    case 'd':
    case 'D': 
      if(Screen::IsWithinBounds(posX+1, posY))
      Controls::MoveCursor(posX+1, posY); break;

    case ' ': 
      if(!(posY < Screen::buff.size() && posX < Screen::COLS)) break;
      Screen::buff[posY].flip(posX);
      Screen::Update();
      break;
  }

  return true;
}


void Controls::MoveCursor(size_t x, size_t y) {
  posX = x;
  posY = y;
  std::cout << "\x1b[" << y+1 << ';' << x+1 << "H";
}
