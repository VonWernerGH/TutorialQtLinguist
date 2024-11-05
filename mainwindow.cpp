#include <QTranslator>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString qstrLenguajeFile = ":/i18n/testMultiLingue_fr_FR.qm";

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
