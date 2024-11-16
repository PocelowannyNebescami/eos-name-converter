#include <iostream>
#include <unistd.h>
#include <vector>
#include "application.hpp"

std::vector<std::string> parse_stdin();

int main(const int arg_num, const char* arg_val[])
{
  const bool ignore_pipe = static_cast<bool>(isatty(fileno(stdin)));
  Application app = ignore_pipe ? Application::parse_args(arg_num, arg_val)
                                : Application::parse_args(parse_stdin());

  return app.run();
}

std::vector<std::string> parse_stdin()
{
  std::vector<std::string> res;
  for (std::string line; std::cin >> line;)
  {
    res.emplace_back(line);
  }

  return res;
}
