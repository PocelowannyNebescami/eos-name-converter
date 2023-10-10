#pragma once

#include <string>
#include <string_view>

class Name
{
public:
  Name(const std::string_view& str);
  Name(const uint64_t num);

  bool is_valid() const;

  uint64_t to_num() const;
  std::string to_string() const;

private:
  constexpr uint8_t char_to_num(const char character) const;

private:
  uint64_t origin = 0;
  bool valid = false;

};
