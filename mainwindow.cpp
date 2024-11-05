/*
 * Este archivo es parte de holaMundoQt.
 *
 * holaMundoQt es software libre: puedes redistribuirlo y/o modificarlo
 * bajo los términos de la Licencia Pública General de GNU publicada por
 * la Free Software Foundation, ya sea la versión 3 de la licencia, o
 * (a tu elección) cualquier versión posterior.
 *
 * Este programa se distribuye con la esperanza de que sea útil,
 * pero SIN NINGUNA GARANTÍA; incluso sin la garantía implícita de
 * COMERCIALIZACIÓN o ADECUACIÓN A UN PROPÓSITO PARTICULAR. Consulta los detalles en la
 * Licencia Pública General de GNU.
 *
 * Deberías haber recibido una copia de la Licencia Pública General de GNU
 * junto con este programa. Si no, consulta <http://www.gnu.org/licenses/>.
 */

#include <QTranslator>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString qstrLenguajeFile = ":/i18n/holaMundoQt_en_US.qm";

    QTranslator translator;
    if (translator.load(qstrLenguajeFile)) {
        qApp->installTranslator(&translator);
        qDebug().noquote() << tr("Archivo de lenguaje:") << qstrLenguajeFile << tr("cargado");
    }else{
        qDebug().noquote() << tr("Error al cargar el archivo:") << qstrLenguajeFile;
    }
    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
