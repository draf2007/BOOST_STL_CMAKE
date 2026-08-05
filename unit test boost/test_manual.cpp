#include <iostream>
#include <windows.h>

bool is_even (int a){
    if (a%2 != 0)
    {
        return true;
    }else{
        return false;
    }
    
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    if (is_even(4)==true){
        std::cout << "Тест 1 проиден: 4 это чётное число!" << std::endl;
    }else{
        std::cout << "Тест 1 провален: 4 должно быть четным числом!" << std::endl;
    }

    if (is_even(5)==false){
        std::cout << "Тест 2 проиден: 5 это не чётное число!" << std::endl;
    }else{
        std::cout << "Тест 2 провален: 5 должно быть нечетным числом!" << std::endl;
    }

    if (is_even(0)){
        std::cout << "Тест 3 проиден: 0 это чётное число!" << std::endl;
    }else{
        std::cout << "Тест 3 провален: 0 должно быть четным числом!" << std::endl;
    }
    std::cout << "Тестирование завершено" << std::endl;
    return 0;
}