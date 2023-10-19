#pragma once

#include "name.hpp"
#include <vector>

class Application
{
public:
  Application();

  static Application parse_args(const std::vector<std::string>& inputs);
  static Application parse_args(const int num, const char* const vals[]);

  int run() const;

private:
  std::vector<Name> parsed;
  std::vector<std::pair<std::string, std::string>> errors;

};
