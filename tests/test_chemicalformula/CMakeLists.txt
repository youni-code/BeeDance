cmake_minimum_required(VERSION 3.5)

# enable_testing()

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

find_package(Qt6 REQUIRED COMPONENTS Test)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(t_chemicalformula tst_t_chemicalformula.cpp)

target_link_libraries(t_chemicalformula Qt6::Test)
target_link_libraries(t_chemicalformula Qt6::Widgets)
target_link_libraries(t_chemicalformula chemicalformula)
target_link_libraries(t_chemicalformula simpleformulaelement)
# target_link_libraries(t_chemicalformula simpleformulaelement)

# add_test(NAME t_chemicalformula COMMAND t_chemicalformula)
