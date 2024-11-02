# Tutorial de programas Multilingüe con Qt Linguist

## Inicio: Creación de la aplicación base.

### Creamos la aplicación desde Qt Creator:

*Iniciaremos con una aplicación muy simple sin manejo multilingue.*

1. **File > New Project**
2. **Chose a Template:** *Application (QT) > Qt Widgets Application > "Choose..."*.
3. **Seleccionar la ubicación del proyecto:** Seleccionar ubicación, darle nombre y oprimir *"Next >"*.
4. **Definir el sistema de construcción:** *CMake > "Next >"*.
5. **Información de la Clase:** *"Next >"*.
6. **Archivo de Traducción:** No seleccionar nada, *"Next >"*.
7. **Selección de Kits:** Usar valores seleccionados, *"Next >"*.
8. **Gestión de Proyectos:** A opción del desarrllador, *"Finish"*.

## Adaptar la aplicación gráfica.

*Utilizaremos Qt Designer para adaptar la aplicación, solo incluira una etiqueta con el texto "Hola Mundo"*

1. **Abrir Qt Designer:** Doble click al archivo mainwindow.ui.
2. **Eliminar Elementos innecesarios:** Eliminar *Menu Bar*, *Status Bar*.
3. **Redimensionar la ventana principal**.
4. **Agregar un QLabel:** Qgregar un QLabel, asignar el texto "Hola Mundo", Ajustar Layout.
5. **Cambiar título de la ventana principal:** Cambiar el título de ventana a *"Hola Mundo"*.

## Simplificar CMakeLists.txt:

*La versión de Qt es superior a 6.0, además no será para iOS, ni Mac, ni Android, ni Windows*

1. *Eliminar las instrucciones de CMakeLists para versión de Qt menor a 6.*

    Las instrucciones en CMake Lists son:
    
    ~~~
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(holaMundoQt
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            docs/TutorialQtLinguist.md
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET holaMundoQt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    else()
        if(ANDROID)
            add_library(holaMundoQt SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(holaMundoQt
                ${PROJECT_SOURCES}
            )
        endif()
    endif()
    ~~~

    Al eliminar las instrucciones que se utilizan para versiones menores a 6, queda así:

    ~~~
    qt_add_executable(holaMundoQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        docs/TutorialQtLinguist.md
    )
    ~~~

2. *Eliminar las instrucciones en CMakeLists.txt correspondientes a implementaciones para Mac OS y Windows.*    

    Eliminar las siguientes instrucciones:
    
    ~~~
    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    if(${QT_VERSION} VERSION_LESS 6.1.0)
      set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.holaMundoQt)
    endif()
    set_target_properties(holaMundoQt PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    ~~~

El código simplificado de CMakeLists.txt es:

    ~~~
    cmake_minimum_required(VERSION 3.16)
    
    project(holaMundoQt VERSION 0.1 LANGUAGES CXX)
    
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    
    set(PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
    )
    
    qt_add_executable(holaMundoQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        docs/TutorialQtLinguist.md
    )
    
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
    ~~~
    

Paragraph.

- bullet
+ other bullet
* another bullet
    * child bullet

1. ordered
2. next ordered

### Third Level Heading

Some *italic* and **bold** text and `inline code`.

An empty line starts a new paragraph.

Use two spaces at the end  
to force a line break.

A horizontal ruler follows:

---

Add links inline like [this link to the Qt homepage](https://www.qt.io),
or with a reference like [this other link to the Qt homepage][1].

    Add code blocks with
    four spaces at the front.

> A blockquote
> starts with >
>
> and has the same paragraph rules as normal text.

First Level Heading in Alternate Style
======================================

Paragraph.

Second Level Heading in Alternate Style
---------------------------------------

Paragraph.

[1]: https://www.qt.io
