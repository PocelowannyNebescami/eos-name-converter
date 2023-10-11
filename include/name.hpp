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
  std::string to_sym() const;
  std::string to_sym_code() const;

private:
  constexpr uint8_t char_to_num(const char character) const;

  static inline bool valid_sym_code(const uint64_t raw);
  static inline std::string sym_code(const uint64_t raw);

private:
  uint64_t origin = 0;
  bool valid = false;

};
