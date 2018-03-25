cmake_minimum_required(VERSION 3.5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
project(comp_compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(comp src/main.cpp src/Parser.cpp src/Parser.h src/FileUtils.h src/Texts.h src/AsmGenerator.cpp src/AsmGenerator.h src/ICodeGenerator.h)