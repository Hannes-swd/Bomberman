cmake_minimum_required(VERSION 3.23)

project(Myproject CXX)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# ALLE .cpp Dateien hier auflisten
add_executable(MyProgram 
    src/main.cpp
    src/map.cpp
    src/globals.cpp
    src/player.cpp
)

target_link_libraries(MyProgram PRIVATE raylib)
target_include_directories(MyProgram PRIVATE ${raylib_SOURCE_DIR}/src)