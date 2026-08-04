#include <iostream>
#include <windows.h>

#define BOOST_TEST_MODULE ManualTestReplacement
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

class EvenNumbers {
    public:
        static const int arity = 1;

        struct iterator {
            iterator() : current(1){}

            int operator*() const {
                return current;
            }

            void operator++() {
                current+=2;
            }
            private:
                int current;
        };

        EvenNumbers() {}
        boost::unit_test::data::size_t size() const {
            return boost::unit_test::data::BOOST_TEST_DS_INFINITE_SIZE;
        }

        iterator begin() const { return iterator(); }
    
};

namespace boost {
    namespace unit_test {
        namespace data {
            namespace monomorphic{
                template<>
                struct is_dataset<EvenNumbers> : boost::mpl::true_ {};
            }
        }
    }
}

bool is_even(int a) {
    return a % 2 == 0;
}

BOOST_DATA_TEST_CASE(test_with_custom_generator, 
    EvenNumbers() ^  // ← Наш бесконечный генератор четных чисел!
    boost::unit_test::data::make({true, true, true, true, true}), // ← Ожидаем, что они все четные (true)
    number, expected) {
    SetConsoleOutputCP(65001);

    std::cout << "Генератор выдал: " << number << ", ожидаем: " << expected << "\n";

    BOOST_CHECK_EQUAL(is_even(number), expected);
}
