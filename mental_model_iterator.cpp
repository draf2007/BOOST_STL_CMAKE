#include <iostream>
#include <windows.h>

class StepByTwo{

    public:
        int current; // У каждого итератора есть текущее значение. Тут храним текущее значение итератора
        StepByTwo(int star_value) : current(star_value){} // Итератору нужно начальное значение, и на старте работы итератора текущее значение равно стартовому
        int operator*(){ return current; } // Операция разыменования для получение текущего значения итератора
        void operator++(int){ current-=2; } // Итератор должен как то передвигаться от значения к значению это и есть метод который передвигает итератор к следующему значению
        bool operator!=(const StepByTwo& other){ return current != other.current; }
};

int main() {

    //Настройка консоли на вывод русского языка
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    StepByTwo begin_it(10);
    StepByTwo end_it(0);

    for (StepByTwo it = begin_it; it != end_it; it++)
    {
        std::cout<<*it<<" "<<std::endl;
    }
    

    return 0;
}