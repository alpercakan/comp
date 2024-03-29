/*
 * Comp Compiler v0.1
 *
 * Author: Alper Çakan
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include "ICodeGenerator.h"
#include "Texts.h"
#include "Parser.h"
#include "AsmGenerator.h"
#include "FileUtils.h"
#include <csignal>

using namespace std;


string InputName;
string OutputName;


/**
 * Strips out the extension of the given file name.
 *
 * @param fileName File name
 * @return The extension-less version of fileName
 */
string stripExt(const std::string &fileName) {
  size_t pos = fileName.find('.');
  string ret;

  if (pos == string::npos)
    return fileName;

  return fileName.substr(0, pos);
}

/**
 * Sets the output file name.
 *
 * If index is nonnegative, then this will use the given arguments to set the
 * output file name.
 * If index is negative, the output name will be the same as InputName, except
 * the extension.
 *
 * @param args Arguments
 * @param index First unprocessed argument index
 * @return Number of arguments consumed on success, -1 on failure
 */
int setOutputName(const vector<string> &args, int index) {
  if (index < 0) {
    OutputName = stripExt(InputName) + OUTPUT_FILE_EXTENSION;
    return 0;
  }

  if (index >= args.size())
    // Expected the file name as arg, but it's not there
    return -1;

  OutputName = args[index];
  return 1;
}

/**
 * Prints the help message.
 *
 * Parameters are just to conform with the signature, and are ignored.
 */
int printHelp(const vector<string> &args, int index) {
  cout << HELP_MESSAGE << endl;
  return 0;
}

/**
 * Processes the arguments and delegates to the command functions when
 * necessary. Sets the global InputName, if it is supplied as an arg.
 *
 * Command functions should conform with the signature:
 * int command(const vector<string> &args, int firstUnprocessedIndex)
 * and should return the number of arguments they have consumed, or -1
 * on failure.
 *
 * @param args Argument list. Must contain at least 1 element.
 * @return 0 if the parameters have been succesfully parsed and all commands
 * have succeeded, (i + 1) if the command at index i has failed, -(i + 1) if
 * the argument at index i was illegal.
 */
int resolveArgs(const vector<string> &args) {
  typedef int (*CMD_FN_SIGNATURE)(const vector<string> &, int);

  // Option to function mapping, so as not to bother with a long switch-case
  static const unordered_map<string, CMD_FN_SIGNATURE> cmdMap =
  {
    { CL_OPT_HELP_LONGHAND, printHelp }, { CL_OPT_HELP_SHORTHAND, printHelp},
    { CL_OPT_OUTNAME_LONGHAND, setOutputName }, { CL_OPT_OUTNAME_SHORTHAND, setOutputName }
  };

  for (size_t i = 0; i < args.size(); /* */) {
    const string &arg = args[i];

    if (i == 0 && !arg.empty() && arg[0] != CL_OPT_PREFIX_CHR) {
      // If the first argument does not begin with -, it is the input file name
      InputName = arg;
      ++i;
      continue;
    }

    auto itFn = cmdMap.find(arg);

    if (itFn == cmdMap.end())
      return -(i + 1);

    int ret = (itFn->second)(args, i + 1);

    if (ret < 0)
      return false;

    i += ret + 1;
  }

  return 0;
}

/**
 * Handles the interrupt signal.
 *
 * @param signal Just to conform the required signature
 */
void interruptHandler(int code) {
  if (code != SIGINT) {
    // Should not come here. Ignore.
    return;
  }

  static bool firstTime = true;

  if (firstTime) {
      cout << endl << INTERRUPT_MESSAGE << endl;
      firstTime = false;
  }
  else
    exit(EXIT_FAILURE);
}


string getParseErrorMessage(Parser::ParseError error) {
  // ParseError to error message mapping
  static const unordered_map<Parser::ParseError, string, std::hash<int>> errorMsgMap = {
    { Parser::ParseError::ILLEGAL_ID_CHARACTER, ILLEGAL_ID_CHARACTER_MESSAGE },
    { Parser::ParseError::NO_ID_ON_LHS, NO_ID_ON_LHS_MESSAGE },
    { Parser::ParseError::POW_PARENTHESES_NOT_CLOSED, POW_PARENTHESES_NOT_CLOSED_MESSAGE },
    { Parser::ParseError::EXPECTED_COMMA_IN_POW, EXPECTED_COMMA_IN_POW_MESSAGE },
    { Parser::ParseError::PARENTHESES_NOT_BALANCED, PARENTHESES_NOT_BALANCED_MESSAGE },
    { Parser::ParseError::EXPECTED_FACTOR, EXPECTED_FACTOR_MESSAGE },
    { Parser::ParseError::EXPECTED_NUMBER, EXPECTED_NUMBER_MESSAGE }
  };

  auto it = errorMsgMap.find(error);

  if (it == errorMsgMap.end()) {
    return UNIDENTIFIED_ERROR_MESSAGE;
  } else {
    return it->second;
  }
}


int main(int argc, char *argv[]) {
  auto startTime = clock();

  signal(SIGINT, interruptHandler);

  vector<string> args;
  args.reserve(argc);

  // First elem of argv is program path, give rest to arg parser
  for (int i = 1; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  if (args.empty()) {
    // Print the help message if there are no arguments
    printHelp({ }, -1);
    return EXIT_SUCCESS;
  }

  int retVal = resolveArgs(args);

  if (retVal == 0) { // All commands were successful
    if (OutputName.empty())
      // Output name is same as input's, if none supplied for the former
      setOutputName({ }, -1);

    auto input = FileUtils::readAllLines(InputName);

    if (input.empty()) {
      cout << FILE_READ_FAILURE_MESSAGE(InputName) << endl;

      return EXIT_FAILURE;
    }

    auto templateFile = FileUtils::readAllLines(TEMPLATE_FILE_NAME);
    if (templateFile.empty()) {
      cout << FILE_READ_FAILURE_MESSAGE(TEMPLATE_FILE_NAME) << endl;
      return EXIT_FAILURE;
    }

    AsmGenerator generator(templateFile);
    Parser parser(input, generator);

    if (!parser.parse()) {
      cout << COMPILATION_FAILURE_MESSAGE(parser.getErrorLine(), getParseErrorMessage(parser.getParseError()));
      return EXIT_FAILURE;
    }

    auto asmCode = generator.getOutput();

    if (asmCode.empty()) {
      cout << CODE_GENERATION_FAILURE_MESSAGE << endl;
      return EXIT_FAILURE;
    }

    if (FileUtils::writeLines(OutputName, asmCode)) {
      cout << COMPILATION_SUCCESS_MESSAGE(OutputName, ((float)(clock() - startTime) / CLOCKS_PER_SEC)) << endl;
    } else {
      cout << FILE_WRITE_FAILURE_MESSAGE(OutputName) << endl;
      return EXIT_FAILURE;
    }
  } else if (retVal > 0) {
    // One of the commands failed
    cout << COMMAND_FAILED_MESSAGE(args[retVal - 1]) << endl;
    return EXIT_FAILURE;
  } else {
    // There was an illegal option
    cout << ILLEGAL_COMMAND_LINE_OPTION_MESSAGE(args[-retVal - 1]) << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
