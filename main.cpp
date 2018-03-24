/*
 * Comp Compiler v0.1
 *
 * Author: Alper Çakan
 */

#include <iostream>
#include <vector>
#include <map>
#include "Texts.h"
#include "Parser.h"
#include "AsmGenerator.h"
#include "FileUtils.h"
#include <stack>

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
    return -1;

  OutputName = args[index];
  return 1;
}

/**
 * Prints the help message.
 *
 * Parameters are just to conform the signature, and are ignored.
 */
int printHelp(const vector<string> &args, int index) {
  cout << HELP_MESSAGE << endl;
  return 0;
}

/**
 * Processes the arguments and delegates to the command functions when
 * necessary. Sets the global InputName, if supplied.
 *
 * Command functions should conform to the signature:
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
  const map<string, CMD_FN_SIGNATURE> cmdMap =
  {
    { CL_OPT_HELP_LONGHAND, printHelp }, { CL_OPT_HELP_SHORTHAND, printHelp},
    { CL_OPT_OUTNAME_LONGHAND, setOutputName }, { CL_OPT_OUTNAME_SHORTHAND, setOutputName }
  };

  for (size_t i = 0; i < args.size(); /* */) {
    const string &arg = args[i];

    if (i == 0 && !arg.empty() && arg[0] != CL_OPT_PREFIX_CHR) {
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
    exit(1);
}


int main(int argc, char *argv[]) {
  time_t startTime = time(nullptr);

  signal(SIGINT, interruptHandler);

  vector<string> args;
  args.reserve(argc);

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "") != 0)
      args.push_back(argv[i]);
  }

  if (args.empty()) {
    // Print help message if there is no argument
    args.push_back(CL_OPT_HELP_LONGHAND);
    return EXIT_SUCCESS;
  }

  int retVal = resolveArgs(args);

  if (retVal == 0) {
    if (OutputName.empty())
      setOutputName({ }, -1);

    /*auto lines = FileUtils::readAllLines(InputName);

    if (lines.empty()) {
      cout << FILE_READ_FAILURE_MESSAGE << endl;

      return EXIT_FAILURE;
    }*/

    Comp::AsmGenerator generator(FileUtils::readAllLines(TEMPLATE_FILE_NAME));
    vector<pair<Comp::AsmGenerator::ExprElemType, string>> deneme;
    deneme.push_back({ Comp::AsmGenerator::ExprElemType::NUMBER, "10" });
    generator.addExprCalc(deneme);
    generator.addPrint();

    if (FileUtils::writeLines(OutputName, generator.getOutput())) {
      cout << COMPILATION_SUCCESS_MESSAGE(OutputName, (time(nullptr) - startTime)) << endl;
    } else {
      cout << COMPILATION_FAILURE_MESSAGE(__LINE__, "Because fuck you") << endl;
    }
    //Parser parser(generator);
  } else if (retVal > 0) {
    cout << COMMAND_FAILED_MESSAGE(args[retVal - 1]) << endl;
  } else {
    cout << ILLEGAL_COMMAND_LINE_OPTION_MESSAGE(args[-retVal - 1]) << endl;
  }

  return EXIT_SUCCESS;
}
