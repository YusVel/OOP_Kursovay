#include "CAR.h"

CAR::CAR() {
    this->spec = new ushort[MAX_SPEC]{0};
    this->picturesPath = new QStringList;
}

CAR::~CAR()
{
    delete []spec;
    delete picturesPath;
}

void CAR::fillCarInfo()
{

}

QString CAR::getBrandModel()
{
    QFile file("listOfBrands.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"Говно не открылось!";
    }
    QTextStream out(&file);
    out<<"hello";
    file.close();
    return "";
}
