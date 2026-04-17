#pragma once
#include "screen/Data.hpp"
#include <string>

class ScreenIF {

  ScreenIF(const ScreenIF &) = delete;
  ScreenIF &operator=(const ScreenIF &) = delete;

public:
  ScreenIF() = default;
  ScreenIF(ScreenIF &&) = default;
  ScreenIF &operator=(ScreenIF &&) = default;
  virtual ~ScreenIF() = default;

  virtual void Init(const std::string &, ScreenData &) = 0;
  virtual bool IsOpen() = 0;
  virtual void Compute(ScreenData &) = 0;
  virtual void Draw(ScreenData &) = 0;

};
