//
// Created by Alper Çakan on 23.03.2018.
//

#ifndef COMP_COMPILER_PARSER_H
#define COMP_COMPILER_PARSER_H

#include <string>
#include <vector>
#include "ICodeGenerator.h"

namespace Comp {
class Parser {
public:

  Parser(const std::vector<std::string> &lines,
         ICodeGenerator &generator);

  bool parse();

  enum ParseError { NONE,
                    ILLEGAL_ID_CHARACTER,
                    NO_ID_ON_LHS };

  ParseError getParseError();
  int getErrorLine();

private:
  ParseError errorReason;
  int errorLine;

  ICodeGenerator &generator;
  const std::vector<std::string> lines;

  bool parseAssignment(std::string);
  bool parseExpr(std::string, bool single = true);

  bool isValidId(const std::string &);

  void trimWhitespace(std::string &);

  // Takes the first unconsumed position, returns the first unconsumed position
  int expr(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int term(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int moreTerms(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int factor(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int moreFactors(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int power(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int id(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int num(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
};

} // namespace Comp


#endif //COMP_COMPILER_PARSER_H
