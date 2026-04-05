#pragma once
#include <bitset>  // std::bitset
#include <cstddef> // size_t
#include <array>

class Screen {
  Screen() = delete;
  Screen(Screen &&) = delete;
  Screen(const Screen &) = delete;
  Screen &operator=(Screen &&) = delete;
  Screen &operator=(const Screen &) = delete;
  ~Screen() = delete;
  static inline void Init(const std::string&);
public:
  static constexpr size_t ROWS{25};
  static constexpr size_t COLS{100};
  static std::array<std::bitset<COLS>,ROWS> buff;
  static void LoadTemplate();
  static void Reset();
  static void Update();
  static bool IsWithinBounds(size_t, size_t);
};
