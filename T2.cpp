#define BOOST_TEST_MODULE FibonacciDatasetTest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/bool.hpp>
#include <iostream>
#include <algorithm>

// ============================================================
// КАСТОМНЫЙ ДАТА-СЕТ: Генератор чисел Фибоначчи
// (Работает по тем же принципам, что и наш класс Range!)
// ============================================================
class Fibonacci {
public:
    // Сообщаем Boost.Test, что этот дата-сет выдает 1 параметр за раз
    static const int arity = 1;

    // Вложенный класс итератора
    struct iterator {
        iterator() : a(1), b(1) {}
        
        // Оператор разыменования: возвращает текущее число Фибоначчи
        int operator*() const { return b; }
        
        // Оператор инкремента: вычисляет следующее число
        void operator++() {
            a = a + b;
            std::swap(a, b);
        }
    private:
        int a, b;
    };

    Fibonacci() {}
    
    // Сообщаем, что этот дата-сет бесконечный
    boost::unit_test::data::size_t size() const { 
        return boost::unit_test::data::BOOST_TEST_DS_INFINITE_SIZE; 
    }
    
    // Возвращаем итератор на начало
    iterator begin() const { return iterator(); }
};

// ============================================================
// РЕГИСТРАЦИЯ КЛАССА КАК ДАТА-СЕТА (Tag Dispatch)
// ============================================================
namespace boost {
namespace unit_test {
namespace data {
namespace monomorphic {
    // Говорим фреймворку: "Да, класс Fibonacci является дата-сетом"
    template<>
    struct is_dataset<Fibonacci> : boost::mpl::true_ {};
}
}
} }

// ============================================================
// ТЕСТЫ
// ============================================================

BOOST_AUTO_TEST_SUITE(test_suite_basic)

// Тест 1: Простая проверка сложения (демонстрация макросов)
BOOST_AUTO_TEST_CASE(simple_check) {
    BOOST_CHECK(1 + 1 == 2);
    BOOST_CHECK_EQUAL(5, 2 + 3);
}

// Тест 2: Демонстрация проблемы с double
BOOST_AUTO_TEST_CASE(double_check_warning) {
    // Это может сработать, а может и нет из-за погрешности float
    // BOOST_CHECK_EQUAL(5.3, 2.1 + 3.2); 
    
    // Правильный способ сравнения double:
    BOOST_CHECK_CLOSE_FRACTION(5.3, 2.1 + 3.2, 0.00001);
}

BOOST_AUTO_TEST_SUITE_END()

// ============================================================
// ТЕСТЫ С ДАТА-СЕТАМИ (Data-Driven Tests)
// ============================================================
BOOST_AUTO_TEST_SUITE(test_gen_dataset)

// Тест 3: Использование нашего кастомного итератора Fibonacci
// Мы комбинируем (^) наш генератор с массивом ожидаемых значений.
// Тест выполнится 6 раз, подставляя пары значений в fibSample и exp.
BOOST_DATA_TEST_CASE(test_fibonacci_sequence, 
    Fibonacci() ^ boost::unit_test::data::make({1, 1, 2, 3, 5, 8}),
    fibSample, exp) {
    
    // Проверяем, что сгенерированное число совпадает с ожидаемым
    BOOST_TEST(fibSample == exp);
}

BOOST_AUTO_TEST_SUITE_END()