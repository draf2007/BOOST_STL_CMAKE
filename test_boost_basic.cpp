#include <iostream>
#include <windows.h>

/*Ручные проверки с помощью BOOST

#define BOOST_TEST_MODULE ManualTestReplacement - объявляем модуль тестирования
#include <boost/test/unit_test.hpp> - подключаем юнит тесты
Функция работу которой тестирую
bool is_even (int a){
    return a%2 == 0;
}

BOOST_CHECK - это тест который проверяет истинность произвольного логического выражения
Пример:
BOOST_AUTO_TEST_CASE(test_is_even){ - объявление группы тестов
    BOOST_CHECK(is_even(4)==true); - первым аргументом вызываем функцию с заданным значением и сравнивает то что вернула функция с true,
                                     если функция вернула true, то результат сравнени true == true - тест проиден, если функция вернула false
                                     то результат сравнения false != true, тест провален
    BOOST_CHECK(is_even(5)!=true); - is_even(5) возвращает true - тест проиден потому что выполняется логическое условие false != true
    BOOST_CHECK(is_even(0)==true);
}

BOOST_CHECK_EQUAL(a,b) - сравнивает два значения если равны тест проиден, если не равны тест провален. Так же BOOST_CHECK_EQUAL(a,b) 
                         выводит в консоль больше информации по проваленому тесту чем BOOST_CHECK
Пример:
BOOST_AUTO_TEST_CASE(test_is_even_equal){
    int c = 3;
    int d = 10;
    int result = c+d;
    BOOST_CHECK_EQUAL(result, 10); - если c+d != 10 тест провален
    BOOST_CHECK_EQUAL(is_even(4), false); - если is_even вернёт true, тест провален так как true != false
    BOOST_CHECK_EQUAL(is_even(5), false);
    BOOST_CHECK_EQUAL(is_even(0), true);
}

BOOST_REQUIRE_EQUAL(a, b) - тоже самое что и BOOST_CHECK_EQUAL(a,b) - прерывает выполнение остальных проверок внутри этого же тестового кейса (функции). 
                            Другие тестовые кейсы (функции) всё равно будут запущены фреймворком. 
                            (как пример: нет смысла продолжать тест если появилось деление на 0)
BOOST_AUTO_TEST_CASE(test_is_even_require){
    BOOST_REQUIRE_EQUAL(is_even(4), true);
    BOOST_REQUIRE_EQUAL(is_even(5), false);
    BOOST_REQUIRE_EQUAL(is_even(0), true);
}

BOOST_CHECK_CLOSE_FRACTION(a,b,tolerance) - тоже самое что и BOOST_CHECK_EQUAL(a,b) - но добавлен 3 параметр допуск (tolerance)
                                            этот тест сравнивает результат выражения над числами с плавающей точкой (a) и сравнивает с 
                                            заданным значением (b), с указанным допуском. При сложении двух чисел с плавающей точкой результат может быть
                                            не точно 2,1 или 5,3 а 5,29999999999. 
                                            Это происходит потому что компьютер хранит числа в двоичной системе (из нулей и единиц). 
                                            Дробные числа вроде 2.1 или 3.2 невозможно представить в двоичной системе абсолютно точно. 
                                            Это точно так же, как в нашей обычной десятичной системе невозможно точно записать одну треть (получится бесконечное 0.3333...)
                                            Поэтому, когда вы складываете 2.1 + 3.2, компьютер получает не ровно 5.3, а что-то вроде 5.300000000000001
                                            Макрос BOOST_CHECK_EQUAL проверяет абсолютное, побитовое равенство. Поскольку 5.300000000000001 не равно 5.3, тест падает.
                                            При работе с double и float в тестах никогда нельзя использовать BOOST_CHECK_EQUAL.
                                            Вместо этого нужно проверять, что числа равны с заданной точностью (допуском)

BOOST_AUTO_TEST_CASE(test_double_trap){
    
    std::cout << "===Test Double Trap Start ===" << std::endl;
    double a = 2.1;
    double b = 3.2;
    double sum = a + b;

    std::cout << "Сумма 2,1 и 3,2 равна: " << sum << std::endl;
    //BOOST_CHECK_EQUAL(sum, 5.3);

    BOOST_CHECK_CLOSE_FRACTION(sum,5.3,0.000001);
}
*/

#define BOOST_TEST_MODULE ManualTestReplacement
#include <boost/test/unit_test.hpp>

bool is_even (int a){
    return a%2 == 0;
}

BOOST_AUTO_TEST_CASE(test_is_even){
    SetConsoleOutputCP(65001);
    std::cout << "===Test Check Start ===" << std::endl;
    BOOST_CHECK(is_even(4)==true);
    BOOST_CHECK(is_even(5)!=true);
    BOOST_CHECK(is_even(0)==true);
}

BOOST_AUTO_TEST_CASE(test_is_even_equal){
    std::cout << "===Test Check Equal Start ===" << std::endl;
    int c = 3;
    int d = 10;

    int result = c+d;
    BOOST_CHECK_EQUAL(result, 13);
    BOOST_CHECK_EQUAL(is_even(4), true);
    BOOST_CHECK_EQUAL(is_even(5), false);
    BOOST_CHECK_EQUAL(is_even(0), true);
}

BOOST_AUTO_TEST_CASE(test_is_even_require){
    
    std::cout << "===Test Require Start ===" << std::endl;
    BOOST_REQUIRE_EQUAL(is_even(4), true);
    BOOST_REQUIRE_EQUAL(is_even(5), false);
    BOOST_REQUIRE_EQUAL(is_even(0), true);
}

BOOST_AUTO_TEST_CASE(test_double_trap){
    
    std::cout << "===Test Double Trap Start ===" << std::endl;
    double a = 2.1;
    double b = 3.2;
    double sum = a + b;

    std::cout << "Сумма 2,1 и 3,2 равна: " << sum << std::endl;
    //BOOST_CHECK_EQUAL(sum, 5.3);

    BOOST_CHECK_CLOSE_FRACTION(sum,5.3,0.000001);
}