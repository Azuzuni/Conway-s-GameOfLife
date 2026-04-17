#pragma once
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

inline std::string SelectTemplate() {
  namespace fs = std::filesystem;
  constexpr char folder[] = "./Templates";
  std::vector<fs::path> files{folder};

  if (!fs::exists(folder) || !fs::is_directory(folder))
    throw std::runtime_error("Folder doesnt exist.");

  for (const auto &entry : fs::directory_iterator(folder))
    if (fs::is_regular_file(entry))
      files.push_back(entry.path());

  if (files.empty())
    throw std::runtime_error("No template file found.");

  for (size_t i{1}; i < files.size(); ++i)
    std::cout << i << ". " << files[i].filename().string() << '\n';

  size_t id{};
  std::cout << "Select template id: ";
  std::cin >> id;
  if (!files[id].empty())
    return (files[id].string());
  return "";
}
