#include "name.hpp"
#include <stdexcept>

Name::Name(const std::string_view& str)
{
  if (str.size() > 13 || str.empty())
  {
    return;
  }

  try
  {
    const uint32_t length = std::min(static_cast<uint32_t>(str.size()), 12u);
    for (uint32_t i = 0; i < length; i++)
    {
      this->origin <<= 5;
      this->origin |= this->char_to_num(str.at(i));
    }
    this->origin <<= (4 + 5 * (12 - length));
    if (str.size() == 13)
    {
      uint64_t character = char_to_num(str.at(12));
      if (character > 0x0Full)
      {
        this->origin = 0;
      }
      this->origin |= character;
    }

    this->valid = true;
  }
  catch (std::exception& e)
  {
    this->valid = false;
  }
}

Name::Name(const uint64_t num)
  : origin(num)
  , valid(true)
{
}

bool Name::is_valid() const
{
  return this->valid;
}

uint64_t Name::to_num() const
{
  return this->origin;
}

std::string Name::to_string() const
{
  constexpr uint64_t mask = 0xF800000000000000ull;
  static const char* charmap = ".12345abcdefghijklmnopqrstuvwxyz";

  if (!(this->valid))
  {
    return std::string();
  }

  std::string res{};
  uint64_t origin = this->origin;
  for (uint8_t i = 0; i < 13; i++, origin <<= 5)
  {
    if (origin == 0)
    {
      return res;
    }

    auto indx = (origin & mask) >> (i == 12 ? 60 : 59);
    res.append(std::string(1, charmap[indx]));
  }

  return res;
}

/**
 * @todo Rid of if-chain
*/
constexpr uint8_t Name::char_to_num(const char character) const
{
  if ( character == '.')
  {
    return 0;
  }
  else if ( character >= '1' && character <= '5' )
  {
    return (character - '1') + 1;
  }
  else if ( character >= 'a' && character <= 'z' )
  {
    return (character - 'a') + 6;
  }

  throw std::invalid_argument(std::string(1, character) + " is not a valid names symbol");
}
