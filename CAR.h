#ifndef CAR_H
#define CAR_H
#include "VECTOR.h"
#include <QWidget>
#include <QStringList>
#include <QString>
#include <QFormLayout>
#include <QFile>
#include <QTextStream>
#define MAX_SPEC 9
enum SPECIFICATIONS
{
    BRAND_MODEL = 0,
    YEAR_OF_MANUFACTURE,
    PRICE,
    ENGINE_CAPACITY,
    POWER,
    MAX_SPEED,
    ACCELERATION,
    FUEL_RATE,
    CLEARENCE
};

class CAR
{
private:
    ushort *spec;
    QStringList *picturesPath;
public:
    CAR();
    CAR(CAR &other);
    CAR& operator=(const CAR &other);
    ~CAR();
    static unsigned int carsQuantity;
    static QStringList listModels;

    void setBrand(ushort brandModel);
    void setYearOfManufacture(ushort yearOfManufacture);
    void setPrice(ushort price);
    void setEngineCapacity(ushort engineCapacity);
    void setPower(ushort power);
    void setMaxSpeed(ushort maxSpeed);
    void setAcceleration(ushort acceleration);
    void setFuelRate(ushort fuelRate);
    void setClearence(ushort clearence);

    QString getBrandStr();
    QString getYearOfManufactureStr();
    QString getPriceStr();
    QString getEngineCapacityStr();
    QString getPowerStr();
    QString getMaxSpeedStr();
    QString getAccelerationStr();
    QString getFuelRateStr();
    QString getClearenceStr();

    ushort getBrand();
    ushort getYearOfManufacture();
    ushort getPrice();
    ushort getEngineCapacity();
    ushort getPower();
    ushort getMaxSpeed();
    ushort getAcceleration();
    ushort getFuelRate();
    ushort getClearence();

    QString getBrandModel();
    void addNewBrandModel(QString newBrandModel);

};

#endif // CAR_H
