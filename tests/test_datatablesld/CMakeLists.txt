cmake_minimum_required(VERSION 3.5)

find_package(Qt6 REQUIRED COMPONENTS Test)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(t_datatablesld tst_t_datatablesld.cpp)

target_link_libraries(t_datatablesld Qt6::Test)
target_link_libraries(t_datatablesld Qt6::Widgets)
target_link_libraries(t_datatablesld datatablesld)
target_link_libraries(t_datatablesld readdatafiles)
target_link_libraries(t_datatablesld element)

add_test(NAME t_datatablesld COMMAND t_datatablesld)
