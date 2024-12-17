#include "application.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

Application::Application()
{
}

Application Application::parse_args(const std::vector<std::string>& inputs)
{
  /**
   * @brief Maximum number of digits for 64 bit integer
  */
  constexpr unsigned int MAX_LENGTH = 20;

  Application app;

  for (const std::string& input : inputs)
  {
    if (input.length() > MAX_LENGTH)
    {
      app.errors.emplace_back(input, "Is too long");

      continue;
    }

    const bool is_num = std::all_of(input.cbegin(), input.cend(),
                                    [](const unsigned char sym)
    {
      return static_cast<bool>(std::isdigit(sym));
    });

    try
    {
      const Name value = is_num ? Name(std::stoul(input)) : Name(input);
      if (value.is_valid())
      {
        app.parsed.emplace_back(value);
      }
      else
      {
        app.errors.emplace_back(input, "Is invalid");
      }
    }
    catch (const std::exception &err)
    {
      app.errors.emplace_back(input, err.what());
    }
  }

  return app;
}

Application Application::parse_args(const int num, const char* const vals[])
{
  std::vector<std::string> args;
  for (int index = 1; index < num; index++)
  {
    args.emplace_back(vals[index]);
  }

  return Application::parse_args(args);
}

int Application::run() const
{
  for (const Name& parse : parsed)
  {
    std::cout << std::setw(13) << std::left  << parse.to_string() << ' '
              << std::setw(20) << std::right << parse.to_num() << ' '
              << std::setw(9)  << parse.to_sym_code() << '\n';
  }

  std::cerr << "\033[91m";
  for (const auto& [error, what] : this->errors)
  {
    std::cerr << (error.length() > 20 ? error.substr(0, 20).append("..") : error)
              << " : " << what << '\n';
  }
  std::cerr << "\033[0m";

  return 0;
}
