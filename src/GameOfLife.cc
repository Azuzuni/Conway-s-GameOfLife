#include "GameOfLife.h"
#include "TemplateSelector.h"
#include "screen/Data.hpp"
#include "screen/ScreenIF.hpp"
#include <bitset>
#include <cstddef>
#include <memory>
#include <utility>

GameOfLife::GameOfLife(ScreenData data, std::unique_ptr<ScreenIF> &&screen)
    : mData(data) {
  mScreen = {std::move(screen)};
  mScreen->Init(SelectTemplate(), mData);
}

inline void GameOfLife::Play() {
  if (mData.isPaused)
    return;
  auto temp = mData.buff;
  for (size_t row{}; row < mData.height; ++row) {
    for (size_t col{}; col < mData.width; ++col) {
      constexpr int directionRow[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      constexpr int directionCol[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
      std::bitset<8> neighbour{0x00};
      for (size_t k{}; k < 8; ++k) {
        size_t r = row + directionRow[k];
        size_t c = col + directionCol[k];
        if (r >= 0 && r < mData.height && c >= 0 && c < mData.width)
          neighbour[k] = mData.buff[r * mData.width + c];
      }
      auto aliveNb = neighbour.count();
      bool isAlive = mData.buff[row * mData.width + col];
      if (aliveNb == 3 || (isAlive && aliveNb == 2))
        temp[row * mData.width + col] = true;
      else
        temp[row * mData.width + col] = false;
    }
  }

  mData.buff = std::move(temp);
}

void GameOfLife::Run() {
  while (mScreen->IsOpen()) {
    mScreen->Compute(mData);
    GameOfLife::Play();
    mScreen->Draw(mData);
  }
}
