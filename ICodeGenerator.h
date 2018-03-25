//
// Created by Alper Çakan on 23.03.2018.
//

#ifndef COMP_COMPILER_ICODEGENERATOR_H
#define COMP_COMPILER_ICODEGENERATOR_H

#include <set>
#include <vector>
#include <string>

/*
 * XXX: Const static member initialization in abstract classes is problematic,
 * just use #define for now.
 */
#define ICODEGEN_OPERATION_POW std::string("^")
#define ICODEGEN_OPERATION_SUM std::string("+")
#define ICODEGEN_OPERATION_MUL std::string("*")

/**
 * Abstract base class for code generator classes.
 */
class ICodeGenerator {
public:

  enum ExprElemType { OPERATION, VARIABLE, NUMBER };

  /**
   * Adds an expression calculation.
   *
   * @param postfix A stack which represent the expression as postfix. Every
   * element of the stack is a pair, consisting of ExprElemType and the actual
   * element. If it is an operation, then the second element of the pair must
   * be one of the operation symbol constants in the class. If the type is
   * Number, element must be a hexadecimal string.
   */
  virtual bool addExprCalc(std::vector<std::pair<ExprElemType, std::string>> postfix) noexcept = 0;

  /**
   * Adds an assignment to the code: lhs = <result of the last expr>
   *
   * @param lhs LHS variable's name
   */
  virtual void addAssignment(const std::string &lhs) noexcept = 0;

  /**
   * Adds a print statement, which will print the result of the last
   * expression.
   */
  virtual void addPrint() noexcept = 0;

  virtual std::vector<std::string> getOutput() noexcept = 0;
};

#endif //COMP_COMPILER_ICODEGENERATOR_H
