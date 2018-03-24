/**
 * Author: Alper Çakan
 *
 * Contains all the texts used in the program
 */

#ifndef COMP_COMPILER_TEXTS_H
#define COMP_COMPILER_TEXTS_H

#include <string>


// General
#define HELP_MESSAGE \
(R"(Comp Compiler v0.1

Compiles the language Comp into A86 Assembly.
handcrafted.asm must be in the same directory as the compiler.

Usage: comp [file_name] <args>

You can omit file_name if you are using an option such as --help.
Other than that, the first argument must be the file name.

Options:
    --help, -h                      Prints this message

    --output, -o [out_file_name]    Sets the name of the output file
)")

#define OUTPUT_FILE_EXTENSION ".asm"

#define TEMPLATE_FILE_NAME "handcrafted.asm"


// Compilation messages
#define COMPILATION_SUCCESS_MESSAGE(FILE_NAME, MS) \
(std::string(R"(The compilation has been completed successfully.
Outputted to )") + FILE_NAME + " in " + std::to_string(MS) + " milliseconds")

#define COMPILATION_FAILURE_MESSAGE(LINE, REASON) \
("Compilation failed on line " + std::to_string(LINE) + R"(:
)" + (REASON))


// Error messages
#define INTERRUPT_MESSAGE \
("Interrupted. I am too young to die! Do it again, if you really want it!")

#define FILE_READ_FAILURE_MESSAGE \
("The input file could not be read.")


// Related to command line arguments
#define ILLEGAL_COMMAND_LINE_OPTION_MESSAGE(OPTION) \
(std::string("Illegal command line option: ") + (OPTION))

#define COMMAND_FAILED_MESSAGE(OPTION) \
(std::string("Command line option ") + (OPTION) + " has failed.")

#define CL_OPT_PREFIX_CHR '-'

#define CL_OPT_HELP_LONGHAND  "--help"
#define CL_OPT_HELP_SHORTHAND "-h"

#define CL_OPT_OUTNAME_LONGHAND  "--output"
#define CL_OPT_OUTNAME_SHORTHAND "-o"


#endif //COMP_COMPILER_TEXTS_H
