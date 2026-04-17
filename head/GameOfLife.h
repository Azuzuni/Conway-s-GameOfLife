#pragma once

#include "screen/Data.hpp"
#include "screen/ScreenIF.hpp"
#include <memory>
class GameOfLife {
  GameOfLife() = delete;
  GameOfLife(const GameOfLife &) = delete;
  GameOfLife &operator=(const GameOfLife &) = delete;
  GameOfLife &operator=(GameOfLife &&) = delete;

  ScreenData mData;
  std::unique_ptr<ScreenIF> mScreen;

  void Play();
 
public:
  GameOfLife(ScreenData data, std::unique_ptr<ScreenIF>&&);
  GameOfLife(GameOfLife &&) = default;
  ~GameOfLife() = default;

  void Run();
};
