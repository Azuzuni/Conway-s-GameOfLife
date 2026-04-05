#include "GameOfLife.h"
#include "Controls.h"
#include "Screen.h"
#include <bitset>
#include <cstddef>
#include <iostream>
#include <thread>
#include <utility>
#include <chrono> 


inline void GameOfLife::Play() {
  auto temp = Screen::buff;
  for(size_t row{}; row < Screen::ROWS; ++row) {
    for(size_t col{}; col < Screen::COLS; ++col) {
      constexpr int directionRow[8] = {-1,-1,-1, 0,0, 1,1,1};
      constexpr int directionCol[8] = {-1, 0, 1,-1,1,-1,0,1};
      std::bitset<8> neighbour{0x00};
      for (size_t k{}; k < 8; ++k) {
        size_t r = row + directionRow[k];
        size_t c = col + directionCol[k];
        if (r >= 0 && r < Screen::ROWS && c >= 0 && c < Screen::COLS)
            neighbour[k] = Screen::buff[r][c];
      }
      auto aliveNb = neighbour.count();
      bool isAlive = Screen::buff[row][col];
      if(aliveNb == 3 || (isAlive && aliveNb == 2)) temp[row].set(col);
      else temp[row].reset(col);
    }
  }
  Screen::buff = std::move(temp);
  Screen::Update();
}

void GameOfLife::Run() {
  Screen::LoadTemplate();
  Controls::Init();
  Controls::MoveCursor(0, 0);
  Screen::Update(); // renders loaded template
  while(true) {
    while(Controls::HandleControl()) continue; // use controls to prepare screen
    std::cout << "\x1b[?25l"; // hide cursor
    while(!Controls::HandleControl()) {
      GameOfLife::Play();
      std::this_thread::sleep_for(std::chrono::milliseconds(66)); // ~15 FPS cap    
    }
    std::cout << "\x1b[?25h"; // show cursor
  }

  Controls::Restore(); // Cleanup: Restores changes made in Init() back to default;
}
