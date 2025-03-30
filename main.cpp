#include "mainwindow.h"
#include "CAR.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);
   // MainWindow w;

    try
    {
        /*
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
    */
        int N = 10;
        VECTOR<int> v(N);

        for(int i = 0;i<N;i++)
        {
            int j = std::rand()%100;
            v.push_back(j);
            qDebug()<<"["<<i<<"]  "<<v[i];
        }
        qDebug()<<"**************";
        v.sort_increase();
        for(int i = 0;i<N;i++)
        {
            qDebug()<<"["<<i<<"]  "<<v[i];
        }

    }
    catch (const char * error)
    {
        qDebug()<<error;
    }

   // w.show();
   // return a.exec();
    return 0;
}
