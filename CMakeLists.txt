cmake_minimum_required(VERSION 3.28)
project(ConsoleRacingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio)

add_executable(game
  main.cpp
  projectmenu.cpp
  CarSelection.cpp
  Car.cpp
  Game.cpp
  checkpoint.cpp
)

target_include_directories(game PRIVATE .)
target_link_libraries(game PRIVATE SFML::Graphics SFML::Audio)