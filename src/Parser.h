//
// Created by Alper Çakan on 23.03.2018.
//

#ifndef COMP_COMPILER_PARSER_H
#define COMP_COMPILER_PARSER_H

#include <string>
#include <vector>
#include "ICodeGenerator.h"

class Parser {
public:

  /**
   * Constructs the instance using the given source code and the output code
   * generator.
   */
  Parser(const std::vector<std::string> &lines,
         ICodeGenerator &generator);

  /**
   * Parses the given code and commands the supplied generator the generate
   * the corresponding output code.
   *
   * @return True on success, false if the code has illegal syntax.
   */
  bool parse();

  enum ParseError { NONE, // No error
                    ILLEGAL_ID_CHARACTER,
                    NO_ID_ON_LHS,
                    POW_PARENTHESES_NOT_CLOSED,
                    EXPECTED_COMMA_IN_POW,
                    PARENTHESES_NOT_BALANCED,
                    EXPECTED_FACTOR,
                    EXPECTED_NUMBER };

  /**
   * @return The parse error which caused parse() to return false, or NONE
   * if parse() returned true.
   */
  ParseError getParseError();

  /**
   * @return The number of the line which caused parse() to return false.
   */
  int getErrorLine();

private:
  ParseError errorReason;
  int errorLine;

  ICodeGenerator &generator;
  const std::vector<std::string> lines;

  bool parseAssignment(std::string);

  /*
   * Give single = false if this expression is parse of a assignment,
   * given single = true if this expressions
   */
  bool parseExpr(std::string, bool single = true);

  bool isValidId(const std::string &);

  void trimWhitespace(std::string &);

  int expr(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int term(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int moreTerms(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int factor(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int moreFactors(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int power(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int id(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
  int num(const std::string&, int, std::vector<std::pair<ICodeGenerator::ExprElemType, std::string>>&);
};


#endif //COMP_COMPILER_PARSER_H
