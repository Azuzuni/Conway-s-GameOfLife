#pragma once

class GameOfLife {
  GameOfLife() = delete;
  GameOfLife(GameOfLife &&) = delete;
  GameOfLife(const GameOfLife &) = delete;
  GameOfLife &operator=(GameOfLife &&) = delete;
  GameOfLife &operator=(const GameOfLife &) = delete;
  ~GameOfLife() = delete;
  static inline void Play();
public:
  static void Run();
};
