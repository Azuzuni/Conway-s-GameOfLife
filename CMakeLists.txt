cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES 
  src/main.cc
  src/GameOfLife.cc
  src/Screen.cc
  src/Controls/Shared.cc
  src/Controls/unix.cc
  src/Controls/win32.cc
)

set(HEADERS
  head/Controls.h
  head/GameOfLife.h
  head/Screen.h
)

add_executable(${PROJECT_NAME} ${SOURCES}) 
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/head/
)


file(COPY ${CMAKE_SOURCE_DIR}/Templates
  DESTINATION ${CMAKE_BINARY_DIR})
