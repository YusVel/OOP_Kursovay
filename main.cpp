#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;

    try
    {
        MainWindow w;
         w.show();
    }
    catch (const char * error)
    {
        qDebug()<<error;
    }
    w.show();
    return a.exec();
}
