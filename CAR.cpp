#include "CAR.h"

unsigned int CAR::carsQuantity = 0;
QStringList CAR:: listModels;

CAR::CAR() {
    this->spec = new ushort[MAX_SPEC]{0};
    if(carsQuantity==0)
    {
        QFile file(QDir::current().absolutePath()+QString("/source/listOfBrands.txt"));
        qDebug()<<QDir::current().absolutePath()+QString("/listOfBrands.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"Ошибка в загрузке названия бренда автомиобиля!";
            throw"ERROR. listOfBrands.txt did not read!";
        }
        QString temp;
        QTextStream in(&file);
        while(in.readLineInto(&temp))
        {
            listModels.append(temp);
        }
        file.close();
    }
    carsQuantity++;
}


CAR::CAR(CAR &other)
{
    for(int i = 0;i <MAX_SPEC;i++)
    {
        this->spec[i] = other.spec[i];
    }
    this->picturesPath = other.picturesPath;
    carsQuantity++;
}

CAR &CAR::operator=( const CAR &other)
{
    for(int i = 0;i <MAX_SPEC;i++)
    {
        this->spec[i] = other.spec[i];
    }
    this->picturesPath = other.picturesPath;
    return *this;
}

CAR::~CAR()
{
    delete []spec;
    --carsQuantity;
    if(carsQuantity==0)
    {
        QFile file(QDir::current().absolutePath()+QString("/source/listOfBrands.txt"));
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"Ошибка при сохранении файла listOfBrands.txt!";
        }
        QString temp;
        QTextStream out(&file);
        for(int i = 0;i<listModels.size();i++)
        {
            out<<listModels.value(i)<<'\n';
        }
        file.close();
    }
}

void CAR::setBrand(ushort brandModel){
    this->spec[BRAND_MODEL] = brandModel;
}

void CAR::setYearOfManufacture(ushort yearOfManufacture){
    this->spec[YEAR_OF_MANUFACTURE] = yearOfManufacture;
}

void CAR::setPrice(ushort price){
    this->spec[PRICE] = price;
}

void CAR::setEngineCapacity(ushort engineCapacity){
    this->spec[ENGINE_CAPACITY] = engineCapacity;
}

void CAR::setPower(ushort power){
    this->spec[POWER] = power;
}

void CAR::setMaxSpeed(ushort maxSpeed){
    this->spec[MAX_SPEED] = maxSpeed;
}

void CAR::setAcceleration(ushort acceleration){
    this->spec[ACCELERATION] = acceleration;
}

void CAR::setFuelRate(ushort fuelRate){
    this->spec[FUEL_RATE] = fuelRate;
}

void CAR::setClearence(ushort clearence){
    this->spec[CLEARENCE] = clearence;
}

void CAR::setPicturesPaths(QStringList &path)
{
    this->picturesPath = path;
}


///////////////////////////////////////////////////////////
QString CAR::getBrandStr(){
    return getBrandModel();
}

QString CAR::getYearOfManufactureStr()
{
    return QString("%1").arg(spec[YEAR_OF_MANUFACTURE]);
}

QString CAR::getPriceStr()
{
    return QString("%1").arg(spec[PRICE]);
}

QString CAR::getEngineCapacityStr()
{
    return QString("%1").arg(spec[ENGINE_CAPACITY]);
}

QString CAR::getPowerStr()
{
    return QString("%1").arg(spec[POWER]);
}

QString CAR::getMaxSpeedStr()
{
    return QString("%1").arg(spec[MAX_SPEED]);
}

QString CAR::getAccelerationStr()
{
    return QString("%1").arg(spec[ACCELERATION]);
}

QString CAR::getFuelRateStr()
{
    return QString("%1").arg(spec[FUEL_RATE]);
}

QString CAR::getClearenceStr()
{
    return QString("%1").arg(spec[FUEL_RATE]);
}

QString CAR::getSpecsStr(int index)
{
    switch(index)
    {
    case 0: return getBrandStr(); break;
    case 1: return getYearOfManufactureStr(); break;
    case 2: return getPriceStr(); break;
    case 3: return getEngineCapacityStr(); break;
    case 4: return getPowerStr(); break;
    case 5: return getMaxSpeedStr(); break;
    case 6: return getAccelerationStr(); break;
    case 7: return getFuelRateStr(); break;
    case 8: return getClearenceStr(); break;
    }
}
//////////////////////////////////////////////////////////
ushort CAR::getSpecs(SPECIFICATIONS index)
{
    return this->spec[index];
}

//////////////////////////////////////////////////////////
ushort CAR::getBrand(){
   return this->spec[BRAND_MODEL];
}

ushort CAR::getYearOfManufacture(){
   return this->spec[YEAR_OF_MANUFACTURE];
}

ushort CAR::getPrice(){
    return this->spec[PRICE];
}

ushort CAR::getEngineCapacity(){
    return this->spec[ENGINE_CAPACITY];
}

ushort CAR::getPower(){
    return this->spec[POWER];
}

ushort CAR::getMaxSpeed(){
    return this->spec[MAX_SPEED];
}

ushort CAR::getAcceleration(){
    return this->spec[ACCELERATION];
}

ushort CAR::getFuelRate(){
    return this->spec[FUEL_RATE];
}

ushort CAR::getClearence(){
    return this->spec[CLEARENCE];
}
/////////////////////////////
CAR& CAR::randomize(long rand)
{
    std::srand(rand);
    this->spec[BRAND_MODEL] = std::rand()%CAR::listModels.size();
    this->spec[YEAR_OF_MANUFACTURE] = std::rand()%30+1994;
    this->spec[PRICE] = std::rand()%55000+10000;
    this->spec[ENGINE_CAPACITY] = std::rand()%3000+1000;
    this->spec[POWER] = std::rand()%200+70;
    this->spec[MAX_SPEED] = std::rand()%170+100;
    this->spec[ACCELERATION] = std::rand()%10000+2000;
    this->spec[FUEL_RATE] = std::rand()%10000+5000;
    this->spec[CLEARENCE] = std::rand()%200+100;
    return *this;
}

////////////////////////////

QString CAR::getBrandModel()
{
    if(spec[SPECIFICATIONS::BRAND_MODEL]>=listModels.size())
    {
        return "No found";
    }
    return listModels.at(spec[SPECIFICATIONS::BRAND_MODEL]);
}

void CAR::addNewBrandModel(QString newBrandModel){
    listModels.append(newBrandModel);
}
