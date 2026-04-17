cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SCREEN_BACKEND CACHE STRING "Screen backend (0=WinAPI, 1=Raylib, 2=ConsoleColor, 3=ConsoleText)")



# ########################################
# RAYLIB SETUP
# ########################################
if(${SCREEN_BACKEND} STREQUAL "1" )
  set(RAYLIB_VERSION 5.5)
  find_package(raylib ${RAYLIB_VERSION} QUIET)
  if (NOT raylib_FOUND)
    include(FetchContent)

    # Disable building extras BEFORE fetching
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
      raylib
      DOWNLOAD_EXTRACT_TIMESTAMP OFF
      URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
      set(FETCHCONTENT_QUIET NO)
      FetchContent_MakeAvailable(raylib)
      set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    endif()
  endif()
endif()



# ########################################
# MY PROGRAM SETUP
# ########################################



set(SOURCES
  src/GameOfLife.cc
)
if(${SCREEN_BACKEND} STREQUAL "0")
  if(WIN32)
    message(WARNING "WinApi implementation was heavily modified by AI as such do not expect much from it.")
    list(APPEND SOURCES
      src/screen/WinApiScreen.cc
    )
  else()
    message(FATAL_ERROR "This preset is not supported on Unix systems.")
  endif()
endif()

if(${SCREEN_BACKEND} STREQUAL "1")
  list(APPEND SOURCES
    src/screen/RaylibScreen.cc
  )
endif()

if((${SCREEN_BACKEND} STREQUAL "2") OR (${SCREEN_BACKEND} STREQUAL "3") )
  list(APPEND SOURCES
    src/screen/ConsoleScreen.cc
    src/Controls/Shared.cc
  )
  if(WIN32)
    list(APPEND SOURCES
      src/Controls/win32.cc
    )
  else()
    list(APPEND SOURCES
      src/Controls/unix.cc
    )
  endif()
endif()


if (WIN32)
  list(APPEND SOURCES
    src/WinMain.cc
  )
  add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
  list(APPEND SOURCES
    src/main.cc
  )
  add_executable(${PROJECT_NAME} ${SOURCES})
endif()

file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/head/*"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SCREEN_BACKEND=${SCREEN_BACKEND})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/head/
)

file(COPY ${CMAKE_SOURCE_DIR}/Templates
  DESTINATION ${CMAKE_BINARY_DIR})


# ########################################
# RAYLIB LINKING
# ########################################
if(${SCREEN_BACKEND} STREQUAL "1")
  target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
  if (UNIX AND NOT APPLE)
      target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
  endif()
endif()
