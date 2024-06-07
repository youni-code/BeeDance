cmake_minimum_required(VERSION 3.5)

project(BeeDance VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h
)

qt6_add_executable(calculator_sld
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${app_icon_resource_windows}
    coresld.h coresld.cpp
    calculationsld.h calculationsld.cpp

    data/data_sld.txt
    file.qrc )

add_subdirectory(formula)
add_subdirectory(widgets)

target_link_libraries(calculator_sld PUBLIC Qt6::Widgets)

target_link_libraries(calculator_sld PUBLIC formula)
target_include_directories(calculator_sld PRIVATE formula)

target_link_libraries(calculator_sld PUBLIC resultwidget)
target_link_libraries(calculator_sld PUBLIC inputwidget)
target_include_directories(calculator_sld PRIVATE widgets)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.calculator_sld)
endif()
set_target_properties(calculator_sld PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS calculator_sld
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_BINARY_DIR}/data
        COMMENT "Copying resources into binary directory")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calculator_sld)
endif()
