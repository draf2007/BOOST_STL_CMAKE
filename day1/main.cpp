#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// Подключаем библиотеку Boost для работы со строками (header-only)
#include <boost/algorithm/string.hpp>

// Подключаем библиотеку Boost для безопасного преобразования типов (header-only)
#include <boost/lexical_cast.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {

    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    std::cout << "=== Тест Boost в VSCode + CMake ===\n\n";

    // 1. Тест boost::algorithm::string
    std::string text = "   Привет, Boost и CMake!   ";
    std::cout << "Оригинал: '" << text << "'\n";

    // Убираем пробелы по краям
    boost::algorithm::trim(text);
    std::cout << "После trim: '" << text << "'\n";

    // Переводим в верхний регистр
    boost::algorithm::to_upper(text);
    std::cout << "В верхнем регистре: '" << text << "'\n\n";

    // 2. Тест boost::lexical_cast (безопасная замена std::stoi / atoi)
    std::string num_str = "42";
    try {
        // Пытаемся преобразовать строку в число
        int number = boost::lexical_cast<int>(num_str);
        std::cout << "Успешно преобразовали строку '" << num_str << "' в число: " << number << "\n";
    } 
    catch (const boost::bad_lexical_cast& e) {
        std::cerr << "Ошибка преобразования: " << e.what() << "\n";
    }

    std::cout << "\n=== Всё работает! Вы готовы к занятию. ===\n";
    return 0;
}