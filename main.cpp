#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <string_view>
#include <vector>
#include "name.hpp"

std::vector<std::string> parse_stdin();
void print_result(const std::vector<std::string>& params);

int main(int arg_num, char* arg_val[])
{
  if (isatty(fileno(stdin)))
  {
    std::vector<std::string> arguments;
    for (int index = 1; index < arg_num; index++)
    {
      arguments.emplace_back(arg_val[index]);
    }

    print_result(arguments);

    return 0;
  }

  print_result(parse_stdin());

  return 0;
}

std::vector<std::string> parse_stdin()
{
  std::vector<std::string> res;
  for (std::string line; std::cin >> line;)
  {
    res.push_back(line);
  }

  return res;
}

void print_result(const std::vector<std::string>& params)
{
  for (const std::string& param : params)
  {
    if (param.length() > 20)
    {
      std::cerr << param << ": is too long" << '\n';

      continue;
    }

    if (std::all_of(param.cbegin(), param.cend(), [](const char sym)
    {
      return std::isdigit(sym);
    }))
    {
      try
      {
        const uint64_t number = std::stoul(param);
        const Name value = Name(number);
        if (value.is_valid())
        {
          std::cout << std::setw(20) << std::left << param << '\t'
                    << std::setw(20) << std::left << number << '\t'
                    << std::setw(13) << std::right << value.to_string() << '\t'
                    << std::setw(9) << std::right << value.to_sym() << '\n';
        }
        else
        {
          std::cerr << param << ": is invalid" << '\n';
        }
      }
      catch (const std::exception &err)
      {
        std::cerr << param << ": " << err.what() << '\n';
      }

      continue;
    }

    const Name value = Name(param);
    if (value.is_valid())
    {
      std::cout << std::setw(20) << std::left << param << '\t'
                << std::setw(20) << std::left << value.to_num() << '\t'
                << std::setw(13) << std::right << value.to_string() << '\t'
                << std::setw(9) << std::right << value.to_sym() << '\n';
    }
    else
    {
      std::cerr << param << ": is invalid" << '\n';
    }
  }
}
