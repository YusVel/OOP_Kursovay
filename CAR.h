#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <QStringList>
#include <QString>
#include <QFormLayout>
#include <QFile>
#include <QTextStream>
#define MAX_SPEC 10
enum SPECIFICATIONS
{
    BRAND_MODEL,
    YEAR_OF_MANUFACTURE,
    PRICE,
    ENGINE_CAPACITY,
    POWER,
    MAX_SPEED,
    ACCELERATION,
    FUEL_RATE,
    CLEARENCE,
    BODY_COLOR
};

class CAR
{
private:
    ushort *spec;
    QStringList *picturesPath;
public:
    CAR();
    ~CAR();
    void fillCarInfo();//todo
private:
    QString getBrandModel();


};

#endif // CAR_H
