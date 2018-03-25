//
// Created by Alper Çakan on 23.03.2018.
//

#ifndef COMP_COMPILER_ASMGENERATOR_H
#define COMP_COMPILER_ASMGENERATOR_H

#include "ICodeGenerator.h"
#include <vector>
#include <unordered_map>

namespace Comp {

class AsmGenerator final : public ICodeGenerator {
public:
  /**
   * @param genTemplate The Assembly code which includes the helper functions
   * that will be used in code generation. Also, this vector should contain
   * two specific lines: ";CODE;" and ";VARS;"
   */
  AsmGenerator(std::vector<std::string> genTemplate);

  bool addExprCalc(std::vector<std::pair<ExprElemType, std::string>> postfix) noexcept override;
  void addAssignment(const std::string &lhs) noexcept override;
  void addPrint() noexcept override;

  /**
   * @return Empty vector on failure, the generated code lines on success.
   */
  std::vector<std::string> getOutput() noexcept override;

private:
  const std::vector<std::string> genTemplate;

  std::vector<std::string> code;

  const std::unordered_map<std::string, std::vector<std::string>> codeMap;

  std::vector<std::string> getInitCode();
  std::vector<std::string> getDeclCode();

  // Set of the variable names
  std::vector<std::string> varSet;

  size_t getVarIndex(const std::string &);

  // Appends b to a
  static void addVecs(std::vector<std::string> &a, const std::vector<std::string> &b);

  void addLines(const std::vector<std::string> &);
};

} // namespace Comp

#endif //COMP_COMPILER_ASMGENERATOR_H
