cmake_minimum_required(VERSION 3.15)

# ВАЖНО: toolchain vcpkg ставим ДО project()!
# FORCE — чтобы переписать старое значение из кэша, если оно там есть
set(CMAKE_TOOLCHAIN_FILE "D:/C/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "" FORCE)

project(HomeJobSTLBoost)

# Для ДЗ понадобятся: тесты + параметры командной строки + файлы
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework program_options filesystem)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
    Boost::unit_test_framework
    Boost::program_options
    Boost::filesystem
    Boost::boost
)

target_compile_features(main PRIVATE cxx_std_20)