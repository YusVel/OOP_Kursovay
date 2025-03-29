#include "mainwindow.h"
#include "CAR.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /*
    try
    {
       CAR one;
        qDebug()<<one.getBrandModel();
       CAR two;
        two.setBrand(500);
       qDebug()<<two.getBrandModel();
       qDebug()<<two.getYearOfManufactureStr();
       qDebug()<<two.getPriceStr();
       qDebug()<<two.getEngineCapacityStr();
       qDebug()<<two.getPowerStr();
       qDebug()<<two.getMaxSpeedStr();
       qDebug()<<two.getAccelerationStr();
       qDebug()<<two.getFuelRateStr();
       qDebug()<<two.getClearenceStr();
    }
    catch (const char * error)
    {
        qDebug()<<error;
    }
    */
    w.show();
    return a.exec();
    return 0;
}
