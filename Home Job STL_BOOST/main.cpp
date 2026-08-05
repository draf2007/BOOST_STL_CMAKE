#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cctype>
#include <map>
#include <fstream>
#include <stdexcept>
#include <set>

/*ДЗ по boost и stl

Задание:
Разбор текстовых файлов и подсчёт частоты слов Поддержка настройки:
Исключение определённых слов или символов
Варианты сортировки и фильтрации
Построить индекс частоты встречаемости слов.
Выводить статистику в файл или на экран в удобочитаемом виде.

Сначала надо получить текст
создаём строку
std::string text = "Hello, world!  This is a test. Hello world.";

Функция ниже определяет что за символ ей пришел если это пробел или спец символ возвращает true
нужна для нарески строки на элементы для добавления в вектор в в функции cut_text()
bool isDelimiter(char c) {
    unsigned char uc = static_cast<unsigned char>(c); - приводи к unsigned char потому что таблица символов от 0 до 255, 
                                                        если придёт отрицательное значение оно будет приобразованно в символ, 
                                                        а минус(-) будет преобразован в число в диапазоне от 0 до 255

    std::isspace(uc) проверяет пробелом является полученный символ или нет
    std::ispunct(uc) проверяет спец.символом является полученный символ или нет
    return std::isspace(uc) || std::ispunct(uc);
}
Можно еще искать пробел или спец символ в полученой подстроке с помощью метода find()
вот так:
bool isDelimiter(char c) {
    static const std::string delims = " \t\n\r.,!?;:()\"'-_"; - набор разделителей для сверки с полученным символом
    return delims.find(c) != std::string::npos; - сверяем полученый символ с символами из набора и возвращаем true если нашли
}

передаём её в функцию которая режет строку на слова и добавляет каждое слово в новый элемент вектора
std::vector<std::string> cut_text(const std::string& text){ - функция ждёт константную ссылку на строку, ссылка нужна что бы не проводить лишнюю операцию копирования,
                                                             а константная она потому что мы только читаем, но не изменяем исходную строку, а отрезанные элементы кладём в вектор
    std::vector<std::string> cut_word; - вектор для хранения отрезанных слов
    std::string current_cut_word; - текущее слово для отправки в вектор cut_word

    for (char cut : text) - проходим по всем по всем символам строки
        {
        if (delimeter(cut)) { - передаём функции delimiter текущий элемент
            if(!current_cut_word.empty()){ - проверяем элемент на пустоту
                cut_word.push_back(current_cut_word); - если элемент не пустой добавляем его в новый вектор,
                current_cut_word.clear(); - очищаем строку
            }
            если кусочек пустой (два разделителя подряд) — просто идём дальше
        }else{
            current_word += cut; Буква или цифра -> добавляем к текущему кусочку
        }
    }
    За последним словом может не быть символа разделителя по этому если не выполнить проверку ниже
    последнее слово из строки не добавится в вектор.
    if (!current_word.empty()) {
        words.push_back(current_word);
        }
    return word;
}

Функция подсчета количества слов
std::map<std::string, int> countWord(const std::vector<std::string>& word){ - на вход ждём вектор из строк

    std::map<std::string, int> freq; - создаем контейнер типа map
    for (const auto& f_word : word) - обходим контейнер в цикле
    {
        freq[f_word]++; - если ключ есть то увеличиваем счетчик на 1, если нет то добавляем в контейнер
    }
    return freq;

Функция нормализации слов !Не работает с кирилицей пока оставил как есть!
std::string toLower(const std::string& word){ - на вход ждём строку
    std::string result = word; - копируем строку
    for (char& c : result)
    {
        c = std::tolower(static_cast<unsigned char>(c)); каждый полученный символ преобразуем в нижний регистр
    }
    return result; - возвращаем строку
    
}

}

Функция чтения из файла, читай свои записи в Obsidian)))
std::string readFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){ throw std::runtime_error("Не удалось открыть файл!"); }

    std::string content;
    std::string line;
    while (std::getline(file,line))
    {
        content += line;
        content += ' '; // добавляем пробел что бы сшить строки и предотвратить слипание строк
    }
    return content;
}


*/

std::vector<std::string> filterStopWords(
    const std::vector<std::string>& words,
    const std::set<std::string>& stopWords
)
{
    std::vector<std::string> result;

    for (const auto& word : words)
    {
        if (!stopWords.count(word))
        {
            result.push_back(word);
        }
        
    }
    return result;
}

std::string readFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){ throw std::runtime_error("Не удалось открыть файл!"); }

    std::string content;
    std::string line;
    while (std::getline(file,line))
    {
        content += line;
        content += ' ';
    }
    return content;
}

std::string toLower(const std::string& word){
    std::string result = word;
    for (char& c : result)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
    
}

// ============================================================
// ТОКЕНИЗАТОР
// Ментальная модель: "ножницы, режущие ленту текста"
// ============================================================

// Вопрос: "Является ли этот символ разделителем?"
// Разделитель = всё, что НЕ буква и НЕ цифра.
// (пробелы, знаки препинания, табуляция, перевод строки и т.д.)
bool isDelimiter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isspace(uc) || std::ispunct(uc);
}

// Разбивает текст на слова по любым разделителям
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> words;   // корзинка для кусочков
    std::string current_word;         // текущий кусочек, который мы "режем"

    for (char c : text) {
        if (isDelimiter(c)) {
            // Встретили разделитель -> отрезаем текущий кусочек
            if (!current_word.empty()) {
                words.push_back(toLower(current_word));
                current_word.clear();  // готовимся резать следующий кусок
            }
            // Если кусочек пустой (два разделителя подряд) — просто идём дальше
        } else {
            // Буква или цифра -> добавляем к текущему кусочку
            current_word += c;
        }
    }

    // Не забываем последнее слово!
    // После него может не быть разделителя (конец ленты)
    if (!current_word.empty()) {
        words.push_back(toLower(current_word));
    }

    return words;
}

std::map<std::string, int> countWord(const std::vector<std::string>& word){

    std::map<std::string, int> freq;
    for (const auto& f_word : word)
    {
        freq[f_word]++;
    }
    return freq;
}

// ============================================================
// MAIN
// ============================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Читаем текст из файла
    std::string text;
    try {
        text = readFile("sample.txt");
    } catch (const std::exception& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "Прочитано символов: " << text.size() << "\n";

    // Этап 1: режем на слова
    std::vector<std::string> words = tokenize(text);
    std::cout << "Слов всего: " << words.size() << "\n";

    // Этап 2: считаем частоту
    auto freq = countWord(words);
    std::cout << "Уникальных слов: " << freq.size() << "\n";

    // Вывод частот
    for (const auto& [word, count] : freq) {
        std::cout << "  " << word << ": " << count << "\n";
    }
    
    /*std::string text = "Hello, мир!  Это test. Привет_world. Hello мир.";

    std::vector<std::string> words = tokenize(text);

    std::cout << "Слова (" << words.size() << " шт.):\n";
    for (const auto& w : words) {
        std::cout << "  [" << w << "]\n";
    }

    auto freq = countWord(words); // получаем контейнер map

    std::cout << "\nЧастота слов (" << freq.size() << " уникальных):\n";
    for (const auto& [word, count] : freq) {  // обходим в цикле для вывода слова и количества раз которое оно встречается
        std::cout << "  " << word << ": " << count << "\n";
    }*/
    return 0;
}