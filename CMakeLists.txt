cmake_minimum_required(VERSION 3.16)

project(holaMundoQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

set(TS_FILES
    holaMundoQt_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

qt_add_executable(holaMundoQt
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    docs/TutorialQtLinguist.md
)

qt_add_translations(
    holaMundoQt
    TS_FILES ${TS_FILES}
)
add_dependencies(holaMundoQt holaMundoQt_lupdate)
add_dependencies(holaMundoQt holaMundoQt_lrelease)

target_link_libraries(holaMundoQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS holaMundoQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(holaMundoQt)
endif()
