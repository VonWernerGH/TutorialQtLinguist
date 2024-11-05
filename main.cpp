#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
