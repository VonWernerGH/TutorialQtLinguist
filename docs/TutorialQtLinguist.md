# Tutorial de programas Multilingüe con Qt Linguist

## Inicio: Creación de la aplicación base.

### Creamos la aplicación desde Qt Creator:

1. **File > New Project**
2. **Chose a Template:** *Application (QT) > Qt Widgets Application > "Choose..."*.
3. **Seleccionar la ubicación del proyecto:** Seleccionar ubicación, darle nombre y oprimir *"Next >"*.
4. **Definir el sistema de construcción:** *CMake > "Next >"*.
5. **Información de la Clase:** *"Next >"*.
6. **Archivo de Traducción:** No seleccionar nada, *"Next >"*.
7. **Selección de Kits:** Usar valores seleccionados, *"Next >"*.
8. **Gestión de Proyectos:** A opción del desarrllador, *"Finish"*.

## Adaptar la aplicación gráfica.

### Utilizar Qt Designer para adaptar la aplicación:

1. **Abrir Qt Designer:** Doble click al archivo mainwindow.ui.
2. **Eliminar Elementos innecesarios:** Eliminar *Menu Bar*, *Status Bar*.
3. **Redimensionar la ventana principal**.
4. **Agregar un QLabel:** Qgregar un QLabel, asignar el texto "Hola Mundo", Ajustar Layout.
5. **Cambiar título de la ventana principal:** Cambiar el título de ventana a *"Hola Mundo"*.


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
