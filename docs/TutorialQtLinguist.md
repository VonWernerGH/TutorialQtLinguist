# Tutorial de programas Multilingüe con Qt Linguist

## Inicio: Creación de la aplicación base.

### Creamos la aplicación desde Qt Creator:

*Iniciaremos con una aplicación muy simple sin manejo multilingüe.*

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

    El código simplificado de *CMakeLists.txt* es:

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

## Convertir la aplicación en una aplicación Multilingüe.

### Agregar requerimientos de la aplicación Multilingüe a ***CMakeLists.txt***

Agregaremos debajo de la línea:

    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    
Las siguientes líneas a *CMakeLists:*

    find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

    set(TS_FILES)
    
- **find_package(...):** Agrega al proyecto la librería *LinguistTools* que es necesario para la compilación de la aplicación multilingüe.
- **set(TS_FILES):** la variable *TS_FILES* contendrá los nombres de los archivos de traducción (*.ts), de momento como no hay archivos de traducción, *TS_FILES* será vacia.

Agregamos la variable *TS_FILES* al final de la definición de la variable PROJECT_SOURCES para incluir los archivos de traducción al proyecto:

    set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

Después de la instrucción *qt_add_executable(...)* agregamos las siguientes líneas:

    qt_add_translations(
        holaMundoQt
        TS_FILES ${TS_FILES}
    )
    add_dependencies(holaMundoQt holaMundoQt_lupdate)
    add_dependencies(holaMundoQt holaMundoQt_lrelease)
    
**qt_add_translations(...) y add_dependencies(...):** Las instrucciones *qt_add_translations()* y *add_dependencies()*, trabajan para el proceso de traducción en varias fases, a continuación explico cada fase, lo que hace y como se involucra dicha instrucción.

### Fase de Configuración (cmake -S ... -B ...)

Utilizando la sintaxis de *[qt_add_translations](https://doc.qt.io/qt-6.2/qtlinguist-cmake-qt-add-translations.html#qt6-add-translations)():*

    qt_add_translations(
        {target}
        TS_FILES {file1.ts} [file2.ts ...]
    )

Tendremos el siguiente proceso:

1. **Iniciación con *qt_add_translations*:**
    - La función *qt_add_translations()* se configura para gestionar archivos *.ts* y genera un listado interno de archivos *.qm* que se usarán durante todas las fases.
    - Durante esta fase, se llama a *lupdate*:
        - Función de *lupdate*: Analiza los archivos fuente de la aplicación junto con los archivos *.ts*, donde se almacenarán las cadenas de texto extraídas del código que necesitan ser traducidas.
        - Se crea un archivo de recursos *[qt_add_resources](https://doc.qt.io/qt-6.2/qt-add-resources.html)()* en la ruta *${CMAKE_CURRENT_BINARY_DIR}/.rcc* con el nombre del objetivo ${target}, incluye archivos **.qm*, los cuales todavia no existen, este archivo de recursos, será ligado al *${target}* en las fases de compilación, este archivo de recursos será actualizado cada vez que se ejecute una configuración del proyecto o una compilación. Los archivos de recursos **.qm* estarán disponibles para los archivos de código desde el archivo de recursos y podrá ser referenciando a travez del *Prefix "/i18n"* y *BASE "${CMAKE_CURRENT_BINARY_DIR}"* como se muestra en el ejemplo:
       
            ~~~
            QString qstrLenguajeFile = ":/i18n/.rcc/${nombre del archivo .ts sin extensión}.qm";
            ~~~
    
        - **Nota Importante:** En esta fase, no se crean ni modifican archivos *.qm*, ni se actualizan archivos *.ts*; sin embargo, CMake establece que archivos *.qm* se generarán en la fase de compilación.

2. **Objetivos Generados Automáticamente:**
    - Al invocar *qt_add_translations()*, se crean automáticamente varios objetivos que son fundamentales para el manejo de las traducciones del proyecto:
        - *${target}_lupdate*: Este objetivo se encarga de ejecutar *lupdate*, que es la herramienta de Qt utilizada para extraer texto traducible de los archivos de código fuente y generar o actualizar los archivos de traducción *.ts*.
        - *${target}_lrelease*: Este objetivo se utiliza para ejecutar *lrelease*, que convierte los archivos *.ts* en archivos binarios *.qm* que son utilizados en tiempo de ejecución por la aplicación.
        - *update_translations:* Este objetivo se utiliza como un objetivo lógico para agrupar los pasos de actualización de traducciones. Dependiendo de cómo esté configurado el CMake, puede ser utilizado para desencadenar actualizaciones de traducciones en un contexto más amplio.
        - *release_translations:* Similar a *update_translations*, este objetivo agrupa los pasos necesarios para liberar traducciones y generar los archivos *.qm*.

### Fase de Compilación (cmake --build .. por primera vez)

1. Ejecuta *qt_add_translations()* Nuevamente:
    - Durante el primer build, se ejecuta *lupdate* nuevamente (a través de *qt_add_translations*) para sincronizar los archivos *.ts* con el código fuente actual.
    - Luego, *lrelease* es llamado para convertir estos archivos *.ts* en archivos *.qm* binarios.

2. Contenido de Archivos *.qm* Iniciales:
    - Los archivos *.qm* generados en este primer build contendrán las cadenas de texto originales, sin traducción, ya que los archivos *.ts* no han sido modificados aún por el traductor.

3. Orden de Ejecución:
    - *qt_add_translations* se ejecuta antes de la compilación del código fuente de la aplicación, asegurando que los archivos *.ts* estén sincronizados antes de generar los archivos *.qm*.

4. Uso de *add_dependencies()*:
    - Para garantizar que los archivos *.ts* se actualicen y que los archivos *.qm* se generen correctamente, es importante establecer las dependencias entre estos objetivos y el ejecutable. Esto se logra con la instrucción *add_dependencies()*.
    - Por ejemplo, al agregar las siguientes líneas en el archivo *CMakeLists.txt*:
    
        ~~~
        add_dependencies(${target} ${target}_lupdate)
        add_dependencies(${target} ${target}_lrelease)
        ~~~
        
    estás especificando que el ejecutable \${target} debe depender de que se ejecute primero el objetivo de actualización de traducciones (*${target}_lupdate*) y luego el objetivo de liberación de traducciones (*${target}_lrelease*). Esto asegura que, al compilar tu proyecto, las traducciones se actualicen y liberen en el orden correcto antes de construir el ejecutable final.

### Proceso de Traducción

1. **Intervención del Traductor:**
    - Una vez realizado el primer build, se abren los archivos *.ts* en Qt Linguist para introducir las traducciones necesarias en cada cadena de texto generada por *lupdate*.

2. **Segundo Build (Después de la Traducción):**
    - Tras introducir las traducciones y guardar los cambios en los archivos *.ts*, es necesario realizar un segundo build (puede forzarse si es necesario) para actualizar los archivos *.qm*.
    - En esta segunda compilación, *lrelease* toma los archivos *.ts* traducidos y genera archivos *.qm* actualizados, esta vez con las traducciones correctas.
    
3. **Archivo de recursos:**
    - El archivo de recursos es creado desde el proceso de configuración y actualizado en el proceso de compilación antes del ligado, al llegar el proceso de ligado, se incluye en el ejecutable para que este disponible al programa.

