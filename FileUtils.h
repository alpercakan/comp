//
// Created by alpercakan on 23.11.2017.
//

#ifndef COMP_COMPILER_FILEUTILS_H
#define COMP_COMPILER_FILEUTILS_H

#include <string>
#include <fstream>
#include <vector>

class FileUtils {

public:
  /**
   * Reads a file.
   *
   * @param name File name
   * @return Returns all the lines read from the file with the given file name;
   * and empty vector if an error occurs.
   */
  static const std::vector<std::string> readAllLines(const std::string &name) {
    std::vector<std::string> res;

    try {
      std::ifstream file(name, std::ifstream::in);

      std::string line;

      while (getline(file, line)) {
          res.push_back(line);
      }

      file.close();
    } catch (std::exception e) {
      return { };
    }

    return res;
  };

  /**
   * Empties and prints all the lines to the file with the given file name.
   *
   * The last line also endline character, due to *NIX definition of a line.
   *
   * @param name File name
   * @param lines Vector of strings
   * @return True on success, false on failure
   */
  static bool writeLines(const std::string &name,
                         const std::vector<std::string> &lines) {
    try {
      std::ofstream file(name, std::ofstream::out);

      for (auto line : lines) {
        file << line << std::endl;
      }

      file.close();
    } catch (std::exception e) {
      return false;
    }

    return true;
  }
};


#endif //COMP_COMPILER_FILEUTILS_H
