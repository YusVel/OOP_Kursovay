#include "mainwindow.h"
#include "VECTOR.h"
#include "CAR.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);
   // MainWindow w;
    try
    {
       CAR one;
        one.fillCarInfo();
    }
    catch (const char * error)
    {
        qDebug()<<error;
    }

   // w.show();
   // return a.exec();
    return 0;
}
