#ifndef CAR_H
#define CAR_H
#include <QWidget>
#include <QStringList>
#include <QString>
#include <QFormLayout>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
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
    static unsigned int carsQuantity;
    static QStringList listModels;

    CAR();
    CAR(CAR &other);
    CAR& operator=(const CAR &other);
    ~CAR();
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

    ushort getSpecs(SPECIFICATIONS index);

    ushort getBrand();
    ushort getYearOfManufacture();
    ushort getPrice();
    ushort getEngineCapacity();
    ushort getPower();
    ushort getMaxSpeed();
    ushort getAcceleration();
    ushort getFuelRate();
    ushort getClearence();
    CAR& randomize(long rand);
    QString getBrandModel();
    void addNewBrandModel(QString newBrandModel);

    friend QDebug operator<<(QDebug stream, CAR &item)
    {
        stream<<item.getBrandModel()<<'\t'
               <<item.getYearOfManufacture()<<" "
               <<item.getPrice()<<" "
               <<item.getEngineCapacity()<<" "
               <<item.getPower()<<" "
               <<item.getMaxSpeed()<<" "
               <<item.getAcceleration()<<" "
               <<item.getFuelRate()<<" "
               <<item.getClearence()<<"\n";
        return stream;
    }
    friend QDataStream& operator<<(QDataStream& stream, CAR &item)
    {
        for(int i = 0;i<MAX_SPEC;i++)
        {
            stream<<item.spec[i];
        }
        stream<<*(item.picturesPath);
        return stream;
    }

    friend QDataStream& operator>>(QDataStream& stream, CAR &item)
    {
        for(int i = 0;i<MAX_SPEC;i++)
        {
            stream>>item.spec[i];
        }
        stream>>*(item.picturesPath);
        return stream;
    }
};

#endif // CAR_H
