cmake_minimum_required(VERSION 3.15)
project(BoostTest)

# Ищем Boost в режиме CONFIG (современный способ, без предупреждений)
find_package(Boost CONFIG REQUIRED COMPONENTS filesystem system regex thread date_time)

# Создаём исполняемый файл
add_executable(main main.cpp)

# Подключаем Boost
target_link_libraries(main PRIVATE 
    Boost::boost
    Boost::filesystem 
    Boost::system
    Boost::regex
    Boost::thread
    Boost::date_time
)

# Стандарт C++17
target_compile_features(main PRIVATE cxx_std_17)