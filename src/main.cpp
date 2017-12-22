#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
#if defined(Q_OS_WIN32)
    a.setStyle(QStyleFactory::create("windowsxp"));
#endif
    return a.exec();
}
