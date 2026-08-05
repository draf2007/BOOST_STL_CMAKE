cmake_minimum_required(VERSION 3.15)
project(BoostLearning)

set(CMAKE_TOOLCHAIN_FILE "D:/C/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "Vcpkg target triplet")

find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

#add_executable(test_manual test_manual.cpp)


#add_executable(test_boost_basic test_boost_basic.cpp)
#target_link_libraries(test_boost_basic PRIVATE Boost::unit_test_framework Boost::boost)
#target_compile_features(test_boost_basic PRIVATE cxx_std_20)

#add_executable(boost_data_set boost_data_set.cpp)
#target_link_libraries(boost_data_set PRIVATE Boost::unit_test_framework Boost::boost)
#target_compile_features(boost_data_set PRIVATE cxx_std_20)

#add_executable(Class_generator_for_boost Class_generator_for_boost.cpp)
#target_link_libraries(Class_generator_for_boost PRIVATE Boost::unit_test_framework Boost::boost)
#target_compile_features(Class_generator_for_boost PRIVATE cxx_std_20)

add_executable(mental_model_iterator mental_model_iterator.cpp)
target_link_libraries(mental_model_iterator PRIVATE Boost::unit_test_framework Boost::boost)
target_compile_features(mental_model_iterator PRIVATE cxx_std_20)
