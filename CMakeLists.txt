cmake_minimum_required(VERSION 3.9)
project(comp_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(comp_compiler main.cpp Parser.cpp Parser.h FileUtils.h Texts.h AsmGenerator.cpp AsmGenerator.h ICodeGenerator.h)