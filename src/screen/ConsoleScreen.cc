#include "screen/ConsoleScreen.hpp"
#include "Controls.h"
#include "screen/Data.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <thread>

template <bool COMPILE_COLORS> ConsoleScreen<COMPILE_COLORS>::~ConsoleScreen() {
  Controls::Restore();
}

template <bool COMPILE_COLORS>
void ConsoleScreen<COMPILE_COLORS>::Init(const std::string &fileName,
                                         ScreenData &data) {
  std::ifstream file{fileName};
  if (!file.is_open())
    throw std::runtime_error("Failed to open template.");

  Controls::Init();
  std::string line{};
  for (size_t row{}; std::getline(file, line) && row < data.height; ++row) {
    for (size_t col{}; col < line.size() && col < data.width; ++col) {
      if (line[col] == '#')
        data.buff[row * data.width + col] = true;
      else
        data.buff[row * data.width + col] = false;
    }
  }

  file.close();
  Draw(data);
}
template <bool COMPILE_COLORS> bool ConsoleScreen<COMPILE_COLORS>::IsOpen() {
  return true;
}

template <bool COMPILE_COLORS>
void ConsoleScreen<COMPILE_COLORS>::Compute(ScreenData &data) {
  if(!Controls::HandleControl(data)) return;
  std::cout << "\x1b[?25h"; // show cursor
  for(bool run{true}; run;) {
    while(Controls::HandleControl(data)) continue;
    Draw(data);
    if(!Controls::HandleControl(data)) run = false;
  }
  std::cout << "\x1b[?25l"; // hide cursor
}

template <bool COMPILE_COLORS>
void ConsoleScreen<COMPILE_COLORS>::Draw(ScreenData &data) {

  std::stringstream output;
  std::pair<size_t, size_t> positon = Controls::GetPosition();
  size_t count{};
  bool prev{false};
  for (ScreenDataType row{}; row < data.height; ++row) {
    for (ScreenDataType col{}; col < data.width; ++col) {
      auto &point{data.buff[row * data.width + col]};
      if (prev != static_cast<bool>(point) && COMPILE_COLORS) {
        output << (point ? "\x1b[47m" : "\x1b[0m");
        prev = point;
      }
      output << (point ? "#" : " ");
    }
    output << "|\n";
  }
  count = std::accumulate(data.buff.begin(), data.buff.end(), 0);
  for (size_t i{}; i < data.width; ++i)
    output << '-';

  Controls::MoveCursor(0, 0);
  std::cout << output.str();
  Controls::MoveCursor(data.width + 3, 0);
  std::cout << "Cells alive: " + std::to_string(count) + "          ";
  Controls::MoveCursor(positon.first, positon.second);
  std::this_thread::sleep_for(std::chrono::milliseconds(66));
}

// hacky way to keep implementation in separate file
template class ConsoleScreen<true>;
template class ConsoleScreen<false>;
