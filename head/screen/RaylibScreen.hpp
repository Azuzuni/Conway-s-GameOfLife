
#pragma once
#include "screen/Data.hpp"
#include "screen/ScreenIF.hpp"
#include <string>
#include <utility>

class RaylibScreen final : public ScreenIF {
  RaylibScreen(const RaylibScreen &) = delete;
  RaylibScreen &operator=(const RaylibScreen &) = delete;
  int cellWidth{};
  int cellHeight{};

  inline std::pair<float, float> ScreenCellPosition();

public:
  RaylibScreen() = default;
  RaylibScreen(RaylibScreen &&) = default;
  RaylibScreen &operator=(RaylibScreen &&) = default;
  virtual ~RaylibScreen();

  void Init(const std::string &, ScreenData &) override;
  bool IsOpen() override;
  void Compute(ScreenData &) override;
  void Draw(ScreenData &) override;
};
