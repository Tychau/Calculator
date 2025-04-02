#include <iostream>
#include "main.h"
#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(add_two_numbers)
{
    BOOST_CHECK(addTwoNums(5, 7) == 12);
}

BOOST_AUTO_TEST_CASE(multiply_two_numbers)
{
    BOOST_CHECK(multiplyTwoNums(3, 4) == 12);
}

BOOST_AUTO_TEST_CASE(add_binary_strings)
{
    BOOST_CHECK(addTwoBinary("101", "11") == "1000");
}