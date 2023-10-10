#include <iostream>
#include <iomanip>
#include <string_view>
#include <vector>
#include "name.hpp"

int main(int arg_num, char* arg_val[])
{
  if (arg_num < 2)
  {
    return 0;
  }

  std::string_view argument;
  for (int index = 1; index < arg_num; index++)
  {
    argument = arg_val[index];
    if (argument.length() > 20)
    {
      std::cerr << argument << ": is too long" << '\n';

      continue;
    }

    if (std::all_of(argument.cbegin(), argument.cend(), [](const char sym)
    {
      return std::isdigit(sym);
    }))
    {
      try
      {
        const uint64_t number = std::stoul(std::string(argument));
        const Name value = Name(number);
        if (value.is_valid())
        {
          std::cout << std::setw(20) << std::left << argument << '\t'
                    << std::setw(20) << std::left << number << '\t'
                    << std::setw(13) << std::right << value.to_string() << '\t'
                    << std::setw(7) << std::right << value.to_sym_code() << '\n';
        }
        else
        {
          std::cerr << argument << ": is invalid" << '\n';
        }
      }
      catch(const std::exception& err)
      {
        std::cerr << argument << ": " << err.what() << '\n';
      }

      continue;
    }

    const Name value = Name(argument);
    if (value.is_valid())
    {
      std::cout << std::setw(20) << std::left << argument << '\t'
                << std::setw(20) << std::left << value.to_num() << '\t'
                << std::setw(13) << std::right << value.to_string() << '\t'
                << std::setw(7) << std::right << value.to_sym_code() << '\n';
    }
    else
    {
      std::cerr << argument << ": is invalid" << '\n';
    }
  }

  return 0;
}
