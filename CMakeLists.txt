cmake_minimum_required(VERSION 3.9)
project(comp_compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(comp src/main.cpp src/Parser.cpp src/Parser.h src/FileUtils.h src/Texts.h src/AsmGenerator.cpp src/AsmGenerator.h src/ICodeGenerator.h)