#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    try
   {

        w.show();
    }
    catch (const char * error)
    {
        qDebug()<<error;
    }

    return a.exec();

}
