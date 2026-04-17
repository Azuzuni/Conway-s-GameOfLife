#pragma once
#include "screen/Data.hpp"
#include "screen/ScreenIF.hpp"
#include <string>

template <bool COMPILE_COLORS = true>
class ConsoleScreen final : public ScreenIF {
  ConsoleScreen(const ConsoleScreen &) = delete;
  ConsoleScreen &operator=(const ConsoleScreen &) = delete;

public:
  ConsoleScreen() = default;
  ConsoleScreen(ConsoleScreen &&) = default;
  ConsoleScreen &operator=(ConsoleScreen &&) = default;
  virtual ~ConsoleScreen();

  void Init(const std::string &, ScreenData &) override;

  virtual bool IsOpen() override;
  virtual void Compute(ScreenData &) override;
  virtual void Draw(ScreenData &) override;
};
