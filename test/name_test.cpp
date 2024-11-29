#include <gtest/gtest.h>
#include "name.hpp"

namespace name_test
{
    struct Test_case
    {
        std::string_view input;
        uint64_t raw;
    };

    const Test_case name_string = { "eosio", 6138663577826885632 };
    // TODO: fill in real value
    const Test_case symbol_string = { "4,EOS", 0 };
    // TODO: fill in real value
    const Test_case symbol_code_string = { "TELOS", 0 };

    TEST(Valid_name_class, from_name_string)
    {
        const Name test_subject{name_string.input};
        ASSERT_TRUE(test_subject.is_valid());
        ASSERT_EQ(test_subject.to_num(), name_string.raw);

        EXPECT_EQ(test_subject.to_string(), name_string.input);
    }

    TEST(Valid_name_class, from_symbol_string)
    {
        const Name test_subject{symbol_string.input};
        ASSERT_TRUE(test_subject.is_valid());
        ASSERT_EQ(test_subject.to_num(), symbol_string.raw);

        EXPECT_EQ(test_subject.to_sym(), name_string.input);
    }

    TEST(Valid_name_class, from_symbol_code_string)
    {
        const Name test_subject{symbol_code_string.input};
        ASSERT_TRUE(test_subject.is_valid());
        ASSERT_EQ(test_subject.to_num(), symbol_code_string.raw);

        EXPECT_EQ(test_subject.to_sym_code(), symbol_code_string.input);
    }

    TEST(Invalid_name_class, from_lengthy_string)
    {
        const Name test_subject{"aaaaaaaaaaaaaaaaaaaaa"};

        EXPECT_FALSE(test_subject.is_valid());
    }

    TEST(Invalid_name_class, from_empty_string)
    {
        const Name test_subject{""};

        EXPECT_FALSE(test_subject.is_valid());
    }

    TEST(Invalid_name_class, from_invalid_character)
    {
        const Name test_subject{"eosio@@@@"};

        EXPECT_FALSE(test_subject.is_valid());
    }
}
