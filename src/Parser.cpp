//
// Created by Alper Çakan on 23.03.2018.
//

#include "Parser.h"

using std::string;
using std::pair;
using std::vector;
using std::exception;

// Use our own checks because isalnum, isspace etc. are locale-dependent
#define IS_SPACE(x) ((x) == '\t' || (x) == ' ' || (x) == '\n' || (x) == '\r')

#define IS_DIGIT(x) \
((x) == '0'  || (x) == '1'  || (x) == '2'  || (x) == '3'  || (x) == '4' ||\
 (x) == '5'  || (x) == '6'  || (x) == '7'  || (x) == '8'  || (x) == '9')

// Classic valid ID: allow alphanumeric and '$', '_'; except for digit at start
#define IS_VALID_ID_CHAR(x, IS_FIRST) \
(string("$_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz").find(x) != string::npos \
&& (!(IS_FIRST) || !IS_DIGIT(x)))

#define IS_VALID_HEX_CHAR(x) \
(IS_DIGIT(x) ||\
 (x) == 'A'  || (x) == 'B'  || (x) == 'C'  || (x) == 'D'  || (x) == 'E' ||\
 (x) == 'F'  || (x) == 'a'  || (x) == 'b'  || (x) == 'c'  || (x) == 'd' ||\
 (x) == 'e'  || (x) == 'f')

// There is no problem about many macros, .cpp is not included by user anyways

typedef vector<pair<ICodeGenerator::ExprElemType, string>> PostfixStack;

Parser::Parser(const std::vector<string> &lines,
               ICodeGenerator &generator) : lines(lines), generator(generator) { }

void Parser::trimWhitespace(string &str) {
  if (str.empty())
    return;

  size_t i = 0, j = str.length() - 1;

  while (IS_SPACE(str[i])) {
    ++i;

    if (i == str.length()) {
      str = "";
      return;
    }
  }

  while (j > i && isspace(str[j]))
    --j;

  str = str.substr(i, j - i + 1);
}

bool Parser::isValidId(const std::string &id) {
  if (id.empty() || !IS_VALID_ID_CHAR(id[0], true))
    return false;

  for (size_t i = 1; i < id.length(); ++i) {
    if (!IS_VALID_ID_CHAR(id[i], false))
      return false;
  }

  return true;
}

Parser::ParseError Parser::getParseError() {
  return errorReason;
}

int Parser::getErrorLine() {
  return errorLine;
}

bool Parser::parse() {
  try {
    for (size_t i = 0; i < lines.size(); ++i) {
      auto line = lines[i];

      trimWhitespace(line);

      if (line.empty())
        continue;

      if (line.find('=') == string::npos) {
        // No '=' sign, it cannot be an assignment
        if (!parseExpr(line)) {
          errorLine = i + 1;
          return false;
        }
      } else {
        // There is '=' sign, it must be an assignment
        if (!parseAssignment(line)) {
          errorLine = i + 1;
          return false;
        }
      }
    }
  } catch (exception e) {
    return false;
  }

  return true;
}

// Assumes whitespaces are trimmed and line contains '='
bool Parser::parseAssignment(string line) {
  auto eqSignPos = line.find('=');

  if (eqSignPos == 0) {
    errorReason = NO_ID_ON_LHS;
    return false;
  }

  string lhs = line.substr(0, eqSignPos - 1),
         rhs = line.substr(eqSignPos + 1);

  trimWhitespace(lhs);
  trimWhitespace(rhs);

  if (!isValidId(lhs)) {
    errorReason = ILLEGAL_ID_CHARACTER;
    return false;
  }

  if (!parseExpr(rhs, false)) {
    return false;
  }

  generator.addAssignment(lhs);

  return true;
}

/*
 * Assumes whitespaces are trimmed.
 * Implements (push-down automata based) LL(k) parser.
 */
bool Parser::parseExpr(string line, bool single) {
  PostfixStack postfix;

  int pos = expr(line, 0, postfix);

  if (pos < 0 || pos < line.length())
    return false;

  generator.addExprCalc(postfix);

  if (single)
    generator.addPrint();

  return true;
}


 /*
  * Methods corresponding to the variables in the grammar.
  *
  * Each of them takes the first unconsumed position, and returns the first
  * unconsumed position; or -1 on failure.
  */

int Parser::expr(const string &str, int index, PostfixStack &ps) {
  if (index < 0 || index >= str.length()) return -1;

  int pos = term(str, index, ps);

  if (pos < 0)
    return -1;

  pos = moreTerms(str, pos, ps);
  if (pos < 0)
    return -1;

  return pos;
}

int Parser::moreTerms(const string &str, int index, PostfixStack &ps) {
  if (index < 0) return -1;

  while (index < str.length() && IS_SPACE(str[index]))
    ++index;

  if (index >= str.length())
    return index;

  if (str[index] != '+')
    return index;

  int pos = term(str, index + 1, ps);
  if (pos < 0)
    return -1;

  ps.push_back({ ICodeGenerator::ExprElemType::OPERATION, ICODEGEN_OPERATION_SUM });

  pos = moreTerms(str, pos, ps);

  if (pos < 0)
    return -1;

  return pos;
}

int Parser::id(const string &str, int index, PostfixStack &ps) {
  if (index < 0 || index >= str.length()) return -1;

  while (index < str.length() && IS_SPACE(str[index]))
    ++index;

  if (index >= str.length())
    return -1;

  int start = index;

  if (!IS_VALID_ID_CHAR(str[index], true)) {
    errorReason = ILLEGAL_ID_CHARACTER;
    return -1;
  }

  do
    ++index;
  while (index < str.length() && IS_VALID_ID_CHAR(str[index], false));

  ps.push_back({ ICodeGenerator::ExprElemType::VARIABLE, str.substr(start, index - start) });

  return index;
}

int Parser::num(const string &str, int index, PostfixStack &ps) {
  if (index < 0 || index >= str.length()) return -1;

  while (index < str.length() && IS_SPACE(str[index]))
    ++index;

  if (index >= str.length())
    return -1;

  int start = index;

  while (index < str.length() && IS_VALID_HEX_CHAR(str[index]))
    ++index;

  ps.push_back({ ICodeGenerator::ExprElemType::NUMBER, str.substr(start, index - start) });

  return index;
}

int Parser::term(const string &str, int index, PostfixStack &ps) {
  if (index < 0 || index >= str.length()) return -1;

  int pos = factor(str, index, ps);

  if (pos < 0)
    return -1;

  pos = moreFactors(str, pos, ps);

  if (pos < 0)
    return -1;

  return pos;
}

int Parser::moreFactors(const string &str, int index, PostfixStack &ps) {
  if (index < 0) return -1;

  while (index < str.length() && IS_SPACE(str[index]))
    ++index;

  if (index >= str.length())
    return index;

  if (str[index] != '*')
    return index;

  int pos = factor(str, index + 1, ps);
  if (pos < 0)
    return -1;

  ps.push_back({ ICodeGenerator::ExprElemType::OPERATION, ICODEGEN_OPERATION_MUL });

  pos = moreFactors(str, pos, ps);

  if (pos < 0)
    return -1;

  return pos;
}

int Parser::factor(const string &str, int index, PostfixStack &ps) {
  if (index < 0 || index >= str.length()) return -1;

  while (index < str.length() && IS_SPACE(str[index]))
    ++index;

  if (index >= str.length()) {
    errorReason = EXPECTED_FACTOR;
    return -1;
  }

  // Use ~4 lookahead to choose which prod rule to recurse on
  if (str[index] == '(') {
    int pos = expr(str, index + 1, ps);

    if (pos >= str.length() || str[pos] != ')') {
      errorReason = PARENTHESES_NOT_BALANCED;
      return -1;
    }

    return pos + 1;
  } else if (IS_DIGIT(str[index])) {
    int pos = num(str, index, ps);

    if (pos < 0) {
      errorReason = EXPECTED_NUMBER;
      return -1;
    }

    return pos;
  } else if (str.substr(index, 3) == "pow") {
    int cpy = index;
    index += 3;

    /*
     * This is why 4 has a '~' before it above:
     * We do not use strictly 4 lookahead, because we are skipping the spaces.
     */
    while (index < str.length() && IS_SPACE(str[index]))
      ++index;

    if (index < str.length() && str[index] == '(') {
      int pos = expr(str, index + 1, ps);

      if (pos < 0)
        return -1;

      if (pos >= str.length() || str[pos] != ',') {
        errorReason = EXPECTED_COMMA_IN_POW;
        return -1;
      }

      pos = expr(str, pos + 1, ps);

      if (pos >= str.length() || str[pos] != ')') {
        errorReason = POW_PARENTHESES_NOT_CLOSED;
        return -1;
      }

      ps.push_back({ ICodeGenerator::ExprElemType::OPERATION, ICODEGEN_OPERATION_POW });
      return pos + 1;
    }

    index = cpy;
  }

  int pos = id(str, index, ps);

  if (pos < 0)
    return -1;

  return pos;
}
