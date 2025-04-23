#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    try
   {
        /*
        const int N  = 10;
        VECTOR<CAR> arr;
        arr.readFromFile("newB.base");
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        arr.sort_increase();
        for(int i = 0;i<arr.getSize();i++)
        {
            qDebug()<<arr[i];
        }
        */
        w.show();
    }
    catch (const char * error)
    {
        qDebug()<<error;
    }

    return a.exec();
    //return 0;
}
