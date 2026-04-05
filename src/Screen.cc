#include "Screen.h"
#include "Controls.h"
#include <bitset>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <array>
#include <fstream>
#include <string>
#include <filesystem>
#include <utility>
#include <vector>

constexpr bool COMPILE_CONSOLE_COLORS{true};
std::array<std::bitset<Screen::COLS>,Screen::ROWS> Screen::buff;

inline void Screen::Init(const std::string& fileName) {
  std::ifstream file{fileName};
  if(!file.is_open()) throw std::runtime_error("Failed to open template.");
  
  std::string line{};
  for(size_t row{}; std::getline(file,line) && row < Screen::ROWS; ++row) {
    for(size_t col{}; col<line.size() && col < Screen::COLS; ++col) {
      if(line[col] == '#') Screen::buff[row].set(col);
      else Screen::buff[row].reset(col);
    }
  }
  file.close();
}


void Screen::LoadTemplate() {
  namespace fs=std::filesystem;
  constexpr char folder[] = "./Templates";
  std::vector<fs::path> files{folder};

  if (!fs::exists(folder) || !fs::is_directory(folder))
    throw std::runtime_error("Folder doesnt exist.");

  for(const auto& entry : fs::directory_iterator(folder))
    if(fs::is_regular_file(entry))
      files.push_back(entry.path());

  if(files.empty())
    throw std::runtime_error("No template file found.");

  for(size_t i{1}; i<files.size(); ++i)
    std::cout << i << ". " << files[i].filename().string() << '\n';
  
  size_t id{};
  std::cout << "Select template id: ";
  std::cin >> id;
  if(!files[id].empty()) Screen::Init(files[id].string());
}

void Screen::Reset() {
  for(auto& point : Screen::buff)
    point.reset();
  Screen::Update();
}

void Screen::Update() {
  std::stringstream output;
  std::pair<size_t, size_t> positon = Controls::GetPosition();
  size_t count{};
  bool prev{false};
  for(const auto& point : Screen::buff) {
    for(size_t i{}; i<Screen::COLS; ++i) {
      if(prev != point[i] && COMPILE_CONSOLE_COLORS) {
        output << ((point[i]) ? "\x1b[47m" : "\x1b[0m"); 
        prev = point[i];
      }
      output << (point[i] ? "#" : " ");
    }
    output << "|\n";
    count += point.count();
  }
  for(size_t i{}; i<Screen::COLS; ++i)
    output<< '-';
  Controls::MoveCursor(0,0);
  std::cout << output.str();

  Controls::MoveCursor(Screen::COLS+3, 0);
  std::cout << "Cells alive: "+std::to_string(count)+"          ";
  
  Controls::MoveCursor(positon.first, positon.second);
}

bool Screen::IsWithinBounds(size_t x, size_t y) {
  if(x >= 0 && x <= Screen::COLS) return true;
  if(y >= 0 && y <= Screen::ROWS) return true;
  return false;
}
