cmake_minimum_required(VERSION 3.5)

project(calculator_sld VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message("QTVERSIONMAJOR" ${QT_VERSION_MAJOR})
message("QTVERSION" ${QT_VERSION})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calculator_sld
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        chemicaltextedit.h chemicaltextedit.cpp
        readdatafiles.h readdatafiles.cpp
        element.h element.cpp
        data/sld_data.txt
        chemicalformula.h chemicalformula.cpp
        simpleformulaelement.h simpleformulaelement.cpp
        coresld.h coresld.cpp
        datatablesld.h datatablesld.cpp
        chemicallabel.h chemicallabel.cpp
        chemicalformulachecking.h chemicalformulachecking.cpp
        # tests/test_datatablesld/CMakeLists.txt
        # tests/test_datatablesld/t_datatablesld.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calculator_sld APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(calculator_sld SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calculator_sld
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(calculator_sld PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

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
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_BINARY_DIR}/data
        COMMENT "Copying resources into binary directory")



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calculator_sld)
endif()


add_library(chemicallabel chemicallabel.cpp chemicallabel.h)
add_library(chemicalformula chemicalformula.cpp chemicalformula.h simpleformulaelement.cpp simpleformulaelement.h)
add_library(element element.cpp element.h)
add_library(simpleformulaelement simpleformulaelement.cpp simpleformulaelement.h)
add_library(datatablesld datatablesld.cpp datatablesld.h)
add_library(readdatafiles readdatafiles.cpp readdatafiles.h)

# target_link_libraries(calculator_sld chemicallabel)
# target_link_libraries(calculator_sld element chemicalformula)

target_link_libraries(chemicallabel Qt6::Widgets)
target_link_libraries(chemicalformula Qt6::Widgets)
target_link_libraries(element Qt6::Widgets)
target_link_libraries(simpleformulaelement Qt6::Widgets)
target_link_libraries(datatablesld Qt6::Widgets)
target_link_libraries(readdatafiles Qt6::Widgets)

add_subdirectory(tests)
