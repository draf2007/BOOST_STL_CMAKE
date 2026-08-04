#include <iostream>
#include <windows.h>

#define BOOST_TEST_MODULE ManualTestReplacement
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

bool is_even(int a) {
    return a % 2 == 0;
}

BOOST_DATA_TEST_CASE(test_is_even_dataset, 
    boost::unit_test::data::make({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), 
    number) {
    SetConsoleOutputCP(65001);
    
    std::cout << "Тестируем число: " << number << "\n";
    
    bool expected = (number % 2 == 0);
    BOOST_CHECK_EQUAL(is_even(number), expected);
}



BOOST_DATA_TEST_CASE(test_is_even_proper, 
    boost::unit_test::data::make({0, 1, 2, 3, 4, 5, 6, 7, 8, 10}) ^
    boost::unit_test::data::make({true, false, true, false, true, false, true, false, true, false}),
    number, expected) {

    std::cout << "Тестируем число: " << number << ", ожидаем: " << expected << "\n";

    BOOST_CHECK_EQUAL(is_even(number), expected);
}