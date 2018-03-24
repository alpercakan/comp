//
// Created by Alper Çakan on 23.03.2018.
//

#include "AsmGenerator.h"

using std::string;
using std::vector;
using std::pair;
using std::find;
using std::to_string;

namespace Comp {

#define POW_CODE {\
    "pop BX",\
    "pop AX",\
    "pop DX",\
    "pop CX",\
    "call POW_DWORD",\
    "push AX",\
    "push BX"\
  }

#define PRINT_CODE {\
    "mov DX, BX",\
    "mov CX, AX",\
    "call PRINT_DWORD",\
    "call PRINT_CLRF"\
  }

#define ADD_CODE {\
    "pop BX",\
    "pop AX",\
    "pop DX",\
    "pop CX",\
    "call ADD_DWORD",\
    "push AX",\
    "push BX"\
  }

#define MUL_CODE {\
    "pop BX",\
    "pop AX",\
    "pop DX",\
    "pop CX",\
    "call MUL_DWORD",\
    "push AX",\
    "push BX"\
  }

#define EXIT_CODE { "call EXIT" }

#define POSTFIX_FINISH_CODE {\
    "pop BX",\
    "pop AX"\
  }

#define PUSH_VAR_CODE(ASM_VAR_NAME) { std::string("ds push [") + (ASM_VAR_NAME) + "]" }
#define PUSH_CONST_CODE(CONST) { std::string("push ") + (CONST) }

#define VAR_DECL_CODE(ASM_VAR_NAME) { ((ASM_VAR_NAME) + std::string(" DW ?")) }
#define VAR_RESET_CODE(ASM_VAR_NAME) { (std::string("ds mov [") + (ASM_VAR_NAME)) + "], 0" }
#define VAR_REG_ASSIGN_CODE(ASM_VAR_NAME, ASM_REG_NAME) { std::string("ds mov [") + (ASM_VAR_NAME) + "], " + (ASM_REG_NAME) }

#define ASM_VAR_NAME_PREFIX std::string("compx")
#define ASM_VAR_NAME_LOW_INFIX std::string("l")
#define ASM_VAR_NAME_HIGH_INFIX std::string("h")
#define ASM_LOW_VAR_NAME(VAR_INDEX)\
  (ASM_VAR_NAME_PREFIX + ASM_VAR_NAME_LOW_INFIX + std::to_string(VAR_INDEX))
#define ASM_HIGH_VAR_NAME(VAR_INDEX)\
  (ASM_VAR_NAME_PREFIX + ASM_VAR_NAME_HIGH_INFIX + std::to_string(VAR_INDEX))

#define CODE_SEGMENT_PLACEHOLDER std::string(";CODE;")
#define DATA_SEGMENT_PLACEHOLDER std::string(";VARS;")

#define LOW_WORD(x) ((x) & 0xFFFF)
#define HIGH_WORD(x) (((x) >> 16) & 0xFFFF)


AsmGenerator::AsmGenerator(vector<string> genTemplate) : codeMap(
    { { OPERATION_POW, POW_CODE },
      { OPERATION_MUL, MUL_CODE },
      { OPERATION_SUM, ADD_CODE } }
  ), genTemplate(genTemplate)
  { }

/**
 * Postcondition:
 * Result of the expression will be in (BX AX).
 */
bool AsmGenerator::addExprCalc(vector<pair<ExprElemType, string>> postfix) {
  for (auto elem : postfix) {
    switch (elem.first) {
      case ExprElemType::OPERATION: {
        auto it = codeMap.find(elem.second);

        if (it == codeMap.end())
          // Invalid operation
          return false;

        addLines(it->second);
      }
      break;

      case ExprElemType::VARIABLE: {
        auto varIndex = getVarIndex(elem.second);

        addLines(PUSH_VAR_CODE(ASM_LOW_VAR_NAME(varIndex)));
        addLines(PUSH_VAR_CODE(ASM_HIGH_VAR_NAME(varIndex)));
      }
      break;

      case ExprElemType::NUMBER: {
        size_t value = stoul(elem.second, nullptr, 16);

        addLines(PUSH_CONST_CODE(to_string(LOW_WORD(value))));
        addLines(PUSH_CONST_CODE(to_string(HIGH_WORD(value))));
      }
    }
  }

  addLines(POSTFIX_FINISH_CODE);

  return true;
}

void AsmGenerator::addAssignment(const string &lhs) {
  addLines(VAR_REG_ASSIGN_CODE(ASM_LOW_VAR_NAME(getVarIndex(lhs)), "AX"));
  addLines(VAR_REG_ASSIGN_CODE(ASM_HIGH_VAR_NAME(getVarIndex(lhs)), "BX"));
}

void AsmGenerator::addPrint() {
  addLines(PRINT_CODE);
}

size_t AsmGenerator::getVarIndex(const std::string &varName) {
  auto it = find(varSet.begin(), varSet.end(), varName);

  if (it == varSet.end()) {
    varSet.push_back(varName);

    return varSet.size() - 1;
  } else {
    return distance(varSet.begin(), it);
  }
}


void AsmGenerator::addVecs(std::vector<std::string> &a, const std::vector<std::string> &b) {
  a.insert(a.end(), b.begin(), b.end());
}

void AsmGenerator::addLines(const std::vector<std::string> &lines) {
  addVecs(code, lines);
}

vector<string> AsmGenerator::getInitCode() {
  vector<string> initCode;

  for (size_t i = 0; i < varSet.size(); ++i) {
    addVecs(initCode, VAR_RESET_CODE(ASM_HIGH_VAR_NAME(i)));
    addVecs(initCode, VAR_RESET_CODE(ASM_LOW_VAR_NAME(i)));
  }

  return initCode;
}

vector<string> AsmGenerator::getDeclCode() {
  vector<string> declCode;

  for (size_t i = 0; i < varSet.size(); ++i) {
    addVecs(declCode, VAR_DECL_CODE(ASM_HIGH_VAR_NAME(i)));
    addVecs(declCode, VAR_DECL_CODE(ASM_LOW_VAR_NAME(i)));
  }

  return declCode;
}

std::vector<std::string> AsmGenerator::getOutput() {
  vector<string> res;

  for (auto line : genTemplate) {
    if (line == CODE_SEGMENT_PLACEHOLDER) {
      addVecs(res, getInitCode());
      addVecs(res, code);
      addVecs(res, EXIT_CODE);
    } else if (line == DATA_SEGMENT_PLACEHOLDER) {
      addVecs(res, getDeclCode());
    } else {
      res.push_back(line);
    }
  }

  return res;
}

} // namespace Comp


