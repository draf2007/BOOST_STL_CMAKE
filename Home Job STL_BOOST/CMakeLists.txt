cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "D:/C/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "" FORCE)
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "" FORCE)
project(HomeJobSTLBoost)

find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework program_options filesystem)

# Фабрика (основная программа)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Boost::program_options Boost::filesystem Boost::boost)
target_compile_features(main PRIVATE cxx_std_20)

# Лаборатория (тесты)
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Boost::boost)
target_compile_features(tests PRIVATE cxx_std_20)
target_compile_definitions(tests PRIVATE WORDFREQ_TESTS)