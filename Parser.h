//
// Created by Alper Çakan on 23.03.2018.
//

#ifndef COMP_COMPILER_PARSER_H
#define COMP_COMPILER_PARSER_H

#include <string>
#include <vector>

class Parser {

  Parser(const std::vector<std::string> &lines);

private:
  const std::vector<std::string> lines;
};


#endif //COMP_COMPILER_PARSER_H
