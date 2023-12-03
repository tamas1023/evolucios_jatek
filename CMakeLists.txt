cmake_minimum_required(VERSION 3.10)
project(EvoluciosJatek VERSION 1.0)
add_executable(jatek main.cpp Palya/palya.cpp Helyek/helyek.cpp Eloleny/eloleny.cpp)
target_compile_options(jatek PRIVATE -Wall)