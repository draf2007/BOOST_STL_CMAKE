#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cctype>
#include <map>
#include <fstream>
#include <stdexcept>
#include <set>
#include <algorithm>
#include <utility>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

/*ДЗ по boost и stl

Задание:
Разбор текстовых файлов и подсчёт частоты слов Поддержка настройки:
Исключение определённых слов или символов
Варианты сортировки и фильтрации
Построить индекс частоты встречаемости слов.
Выводить статистику в файл или на экран в удобочитаемом виде.

Сначала надо получить текст
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

Функция записи в файл, читай свои записи в Obsidian)))
void writeToFile(const std::vector<std::pair<std::string, int>>& sorted,
                 const std::string& filename)
{
    std::ofstream file(filename);  // открываем "трубу" для записи

    // Если не удалось создать/открыть файл — сообщаем об ошибке
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл: " + filename);
    }

    // Заголовок для удобочитаемости (требование ДЗ)
    file << "=== Статистика частоты слов ===\n";
    file << "Уникальных слов: " << sorted.size() << "\n";
    file << "--------------------------------\n";

    // Записываем каждое слово и его частоту
    for (const auto& [word, count] : sorted) {
        file << word << ": " << count << "\n";
    }

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

Функция проверки текста в файле на наличие слов из черного списка
std::vector<std::string> filterStopWords(const std::vector<std::string>& words, const std::set<std::string>& stopWords) - на вход ждём вектор строк и множество содержащее черный список слов
{
    std::vector<std::string> result; - вектор для хранения резултата фильтрации

    for (const auto& word : words) - проходим в цикле по вектору и проверяем каждый элемент на нахождение в черном списке
    {
        if (!stopWords.contains(word)) - если в списке нет
        {
            result.push_back(word); - добавляем в вектор result
        }
    }
    return result;
}

сортировка по частоте 
std::vector<std::pair<std::string,int>> sortByFreq(const std::map<std::string, int>& freq){ - на вход ждём map

    std::vector<std::pair<std::string,int>> result(freq.begin(), freq.end()); - копируем map в vector, теперь в каждом элементе вектора лежит пара из map в виде std::pair
                                                                                std::pair это шаблон класса который позволяет хранить два связанных значения разных типов.
                                                                                map это контейнер для нескольких значений типа ключ : значение, 
                                                                                а std::pair это что-то похожее на переменную, только хранящую в себе пару связанных значений
                                                                                к которым можно обратится a.first b.second,
                                                                                вектору всё равно что лежит в его элементах, это даёт возможность обратится к элементу вектора

    std::sort(result.begin(),result.end(),[](const auto& a, const auto& b){ return a.second > b.second; }); - функция сортировки описана у меня в заметке Obsidian

    return result;
}


Структурные привязки (structured bindings) — это введенная в стандарте C++17 языковая конструкция, 
                                             которая позволяет распаковать несколько значений из массивов, 
                                             пар, кортежей или структур в отдельные именованные переменные за один шаг
Пример:
std::pair<int, const char*> get_data() {
    return {1, "Oмск"};
}

int main() {
        
    auto [id, name] = get_data(); - Распаковываем пару в переменные id и name
    std::cout << id << ": " << name << '\n';
}

или как у меня в цикле:
std::cout << "Сортировка по частоте: " << std::endl;
    for (const auto& [word, count] : topWord) - topWord это вектор хранящий в своих элементах std::pair
    {
        std::cout << word <<": "<< count << std::endl;
    }
тут в цикле я обращаюсь к каждому элементу вектора, и при помощи structured bindings вытаскиваю два связанных значения из std::pair (.first и .second)
*/

std::vector<std::pair<std::string,int>> sortByFreq(const std::map<std::string, int>& freq){

    std::vector<std::pair<std::string,int>> result(freq.begin(), freq.end());

    std::sort(result.begin(),result.end(),[](const auto& a, const auto& b){ return a.second > b.second; });

    return result;
}

std::vector<std::string> filterStopWords(
    const std::vector<std::string>& words,
    const std::set<std::string>& stopWords
)
{
    std::vector<std::string> result;

    for (const auto& word : words)
    {
        if (!stopWords.contains(word))
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

std::set<std::string> readStopWords(const std::string& filename) {
    std::ifstream file(filename);  // открываем файл со списком

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл стоп-слов: " + filename);
    }

    std::set<std::string> stopWords;  // чёрный список
    std::string word;

    // Читаем файл построчно: каждая строка = одно стоп-слово
    while (std::getline(file, word)) {
        // ВАЖНО ДЛЯ WINDOWS: убираем \r в конце строки.
        // В Windows конец строки = \r\n, getline читает до \n,
        // но \r остаётся в строке. Без этого "и\r" != "и".
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }

        // Пропускаем пустые строки
        if (!word.empty()) {
            stopWords.insert(word);  // добавляем в чёрный список
        }
    }

    return stopWords;
}

void writeToFile(const std::vector<std::pair<std::string, int>>& sorted,
                 const std::string& filename)
{
    std::ofstream file(filename);  // открываем "трубу" для записи

    // Если не удалось создать/открыть файл — сообщаем об ошибке
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл: " + filename);
    }

    // Заголовок для удобочитаемости (требование ДЗ)
    file << "=== Статистика частоты слов ===\n";
    file << "Уникальных слов: " << sorted.size() << "\n";
    file << "--------------------------------\n";

    // Записываем каждое слово и его частоту
    for (const auto& [word, count] : sorted) {
        file << word << ": " << count << "\n";
    }
}

std::string toLower(const std::string& word){
    std::string result = word;
    for (char& c : result)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
    
}

bool isDelimiter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isspace(uc) || std::ispunct(uc);
}

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> words;
    std::string current_word;
    for (char c : text) {
        if (isDelimiter(c)) {
            if (!current_word.empty()) {
                words.push_back(toLower(current_word));
                current_word.clear();  
            }
            
        } else {
            
            current_word += c;
        }
    }
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

#ifndef WORDFREQ_TESTS
int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    
    po::options_description desc("Доступные параметры");
    desc.add_options()
        ("help,h", "Показать эту справку")
        ("input,i", po::value<std::string>()->default_value("sample.txt"),
            "Входной текстовый файл")
        ("output,o", po::value<std::string>()->default_value("output.txt"),
            "Выходной файл со статистикой")
        ("stopwords,s", po::value<std::string>()->default_value("stop_words.txt"),
            "Файл Blacklist");

    po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
        } catch (const std::exception& ex) {
            std::cout << "Ошибка параметров: " << ex.what() << std::endl;
            std::cout << desc << std::endl;
            return 1;
        }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    std::string inputFile     = vm["input"].as<std::string>();
    std::string outputFile    = vm["output"].as<std::string>();
    std::string stopwordsFile = vm["stopwords"].as<std::string>();

    std::cout << "Входной файл:   " << inputFile << std::endl;
    std::cout << "Выходной файл:  " << outputFile << std::endl;
    std::cout << "Файл стоп-слов: " << stopwordsFile << std::endl;
    std::cout << std::endl;

    std::string text;
    try {
        text = readFile(inputFile);
    } catch (const std::exception& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "Прочитано символов: " << text.size() << std::endl;

    std::vector<std::string> words = tokenize(text);
    std::cout << "Слов всего: " << words.size() << std::endl;

    std::set<std::string> stopWords;
        try {
           stopWords = readStopWords(stopwordsFile);
            } catch (const std::exception& ex) {
    std::cout << "Ошибка: " << ex.what() << std::endl;
            return 1;
            }
    std::cout << "Загружено стоп-слов: " << stopWords.size() << "\n";

    std::vector<std::string> filtered = filterStopWords(words, stopWords);
    std::cout << "Слов после фильтрации: " << filtered.size() << std::endl;

    auto freq = countWord(filtered);
    std::cout << "Уникальных слов: " << freq.size() << std::endl;

    for (const auto& [word, count] : freq) {
        std::cout << word << ": " << count << std::endl;
    }

    auto topWord = sortByFreq(freq);

    std::cout << "Сортировка по частоте: " << std::endl;
    for (const auto& [word, count] : topWord)
    {
        std::cout << word <<": "<< count << std::endl;
    }

    try {
        writeToFile(topWord, outputFile);
        std::cout << "\nРезультат записан в output.txt\n";
    } catch (const std::exception& ex) {
        std::cout << "Ошибка записи: " << ex.what() << std::endl;
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
#endif