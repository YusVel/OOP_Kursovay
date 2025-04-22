#include "mainwindow.h"
#include <qwindowdefs.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{

    pathFile = new QString;
    pathFoto = new QStringList;
    loadStyleSheet();
    setTableView();
    setMainMenuBar();
    setToolBar();
    setStatusBar();

    lableFoto = new QLabel(this);
    lableFoto->setStyleSheet("border: 1px solid grey;");
    lableFoto->setText("FOTO");
    lableFoto->setAlignment(Qt::AlignCenter);
    lableFoto->setGeometry(QRect(260,360,540,335));
    lableFoto->setScaledContents(true);

    nextFoto = new QPushButton(">>>>>",this);
    nextFoto->setGeometry(799,359,100,25);
    QObject::connect(nextFoto,&QPushButton::clicked,this,[this](){
        this->indexFoto++;
        this->tableData->clicked((this->tableData)->currentIndex());
        qDebug()<<"IndexFoto: "<<indexFoto;
    });
    previosFoto = new QPushButton("<<<<<",this);
    previosFoto->setGeometry(161,359,100,25);
    QObject::connect(previosFoto,&QPushButton::clicked,this,[this](){
        this->indexFoto--;
        this->tableData->clicked((this->tableData)->currentIndex());
        qDebug()<<"IndexFoto: "<<indexFoto;
    });

    nextFoto->setEnabled(false);
    previosFoto->setEnabled(false);

    vlayout = new QVBoxLayout;
    vlayout->addWidget(tableData);
    vlayout->setAlignment(Qt::AlignCenter);
    vlayout->setGeometry(QRect(10,55,1030,300));
    vlayout->addWidget(lableFoto);

    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowTitle("Курсовая работа по ООП (class CAR)");
    this->resize(600,700);
    this->setFixedSize(1050,700);

    QObject::connect(this,SIGNAL(appearNewCar()),SLOT(addNewCarToModel()));
    QObject::connect(tableData,SIGNAL(clicked(QModelIndex)),this,SLOT(showFotoOfCar(QModelIndex)));


    icon = new QIcon(QDir::current().absolutePath()+QString("/source/mainWindowIco.ico"));
    this->setWindowIcon(*icon);

}

MainWindow::~MainWindow() {

}


void MainWindow::setMainMenuBar()
{
    mainMenuBar = new QMenuBar(this);
    setFileMenu();
    setSettingMenu();
    setHelpMenu();
    this->setMenuBar(mainMenuBar);
}

void MainWindow::setFileMenu()
{
    fileMenu = new QMenu(tr("Файл"),this);
    openFile =  fileMenu->addAction(tr("Открыть"));
    saveFile = fileMenu->addAction(tr("Сохранить"));
    saveAsFile = fileMenu->addAction(tr("Сохранить как"));
    exit = fileMenu->addAction(tr("Выход"));

    QObject::connect(exit,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(openFile,SIGNAL(triggered()),this,SLOT(setFileNameToOpen()));

    QObject::connect(saveAsFile,SIGNAL(triggered()),this,SLOT(setFileNameToSave()));
    mainMenuBar->addMenu(fileMenu);
}

void MainWindow::setSettingMenu()
{
    settingMenu = new QMenu(tr("Настройки"),this);

    mainMenuBar->addMenu(settingMenu);
}

void MainWindow::setHelpMenu()
{
    helpMenu = new QMenu(tr("Справка"),this);

    mainMenuBar->addMenu(helpMenu);
}

void MainWindow::setTableView()
{
    tableData = new QTableView(this);
    tableData->setStyleSheet(*styleSheet);
}

void MainWindow::setToolBar()
{
    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    openFileTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/openFileIco.ico")),"",QKeySequence("Ctrl+O"));
    openFileTool->setToolTip("Открыть");
    saveFileTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/saveIco.ico")),"",QKeySequence("Ctrl+S"));
    saveFileTool->setToolTip("Сохранить");
    saveAsFileTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/saveAsIco.ico")),"");
    saveAsFileTool->setToolTip("Сохранить как");
    addTableTool  = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/addTableIco.ico")),"");
    addTableTool->setToolTip("Создать новую таблицу");
    addCarTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/addCarIco.ico")),"");
    addCarTool->setToolTip("Добавить новое ТС");
    deleteCarTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/deleteCarIco.ico")),"");
    deleteCarTool->setToolTip("Удалить");
    printTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/printIco.ico")),"",QKeySequence("Ctrl+P"));
    printTool->setToolTip("Печать");
    helpTool = toolBar->addAction(QIcon(QDir::current().absolutePath()+QString("/source/helpIco.ico")),"");
    helpTool->setToolTip("Справка");

    QObject::connect(openFileTool,SIGNAL(triggered()),this,SLOT(setFileNameToOpen()));
    QObject::connect(saveFileTool,SIGNAL(triggered()),this,SLOT(saveDataToFile()));
    QObject::connect(saveAsFileTool,SIGNAL(triggered()),this,SLOT(saveAsDataToFile()));
    QObject::connect(addCarTool,SIGNAL(triggered()),this,SLOT(addNewCar()));
    QObject::connect(deleteCarTool,SIGNAL(triggered()),this,SLOT(deleteCarFromTable()));
    QObject::connect(addTableTool,SIGNAL(triggered()),this,SLOT(createNewTable()));
    QObject::connect(helpTool,SIGNAL(triggered()),this,SLOT(showInfo()));
    QObject::connect(printTool,SIGNAL(triggered()),this, SLOT(printTable()));

    this->addToolBar(Qt::TopToolBarArea,toolBar);
}

void MainWindow::setStatusBar()
{
    statusBar = new QStatusBar(this);
    this->QMainWindow::setStatusBar(statusBar);
}

void MainWindow::loadStyleSheet()
{
    QFile file(QDir::current().absolutePath()+QString("/source/styleSheet.txt"));
    file.open(QIODeviceBase::ReadOnly);
    styleSheet = new QString;
    *styleSheet = QLatin1String(file.readAll());
    file.close();
}

void MainWindow::setFotoPathFilesToCar(CAR &car)
{
    car.picturesPath = QFileDialog::getOpenFileNames(this);
}

void MainWindow::setFileNameFoto()
{
    *pathFoto = QFileDialog::getOpenFileNames(this,"Укажите путь к ФОТО");
    qDebug()<<*pathFoto;
}

void MainWindow::setFileNameToOpen()
{
    *pathFile = QFileDialog::getOpenFileName(this,"Открыть","*.base");
    if(*pathFile!="")
    {
        loadDataToTable();
    }
}

void MainWindow::setFileNameToSave()
{

    *pathFile = QFileDialog::getSaveFileName(this,"Сохранить как",QDir::currentPath(),"База данных(*.base)");

    qDebug()<<*pathFile;
}

void MainWindow::loadDataToTable()
{
    DATA.readFromFile(*pathFile);
    qDebug()<<"Загружено: "<<DATA.getSize()<<"авто.";
    this->setWindowTitle(QString("Курсовая работа по ООП (class CAR) %1").arg(*pathFile));
    if(model==NULL)
    {
        model = new QStandardItemModel(DATA.getSize(),10);
    }
    else
    {
        model->clear();
        model = new QStandardItemModel(DATA.getSize(),10);
    }

    model->setHeaderData(0,Qt::Horizontal,"МАРКА/МОДЕЛЬ");
    model->setHeaderData(1,Qt::Horizontal,"   Год   ");
    model->setHeaderData(2,Qt::Horizontal,"ЦЕНА, руб");
    model->setHeaderData(3,Qt::Horizontal,"ОБЪЕМ ДВ.,\nсм. куб.");
    model->setHeaderData(4,Qt::Horizontal,"МОЩНОСТЬ ДВ.\n л.с.");
    model->setHeaderData(5,Qt::Horizontal,"МАКС. СКОРОСТЬ,\nкм/ч");
    model->setHeaderData(6,Qt::Horizontal,"УСКОРЕНИЕ,\n100 км/ч за n cек.");
    model->setHeaderData(7,Qt::Horizontal,"РАСХОД ТОПЛИВА,\nлит. на 100 км");
    model->setHeaderData(8,Qt::Horizontal,"КЛИРЕНС,\nмм");
    model->setHeaderData(9,Qt::Horizontal,"ФОТО");


    for(int row = 0;row<DATA.getSize();row++)
    {
        for(int col = 0;col<MAX_SPEC;col++)
        {
            model->setItem(row,col,new QStandardItem(DATA[row].getSpecsStr(col)));
            if(col!=0)
            {
                model->item(row,col)->setTextAlignment(Qt::AlignCenter);
                model->item(row,col)->setData(QVariant(DATA[row].getSpecs(SPECIFICATIONS(col))),2);
            }
        }
    }

    tableData->setModel(model);
    tableData->showGrid();
    tableData->setSelectionMode(QAbstractItemView::SingleSelection);
    tableData->setWordWrap(true);

    QHeaderView *horizontalHeader = tableData->horizontalHeader();
    QHeaderView *verticallHeader = tableData->verticalHeader();

    if(true) //
    {
        horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
        verticallHeader->setSectionResizeMode(QHeaderView::Interactive);
        horizontalHeader->setStretchLastSection(true);
        horizontalHeader->setStyleSheet(*styleSheet);
        verticallHeader->setStyleSheet(*styleSheet);
    }

    QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(cellDataChenged(QStandardItem*)));
}

void MainWindow::saveDataToFile()
{
    if(*pathFile!="")
    {
        DATA.writeToFile(*pathFile);
        qDebug()<<"Сохранено: "<<DATA.getSize()<<"авто."<<*pathFile;
    }
    else { qDebug()<<"Отсутствует путь для сохранения файла";}
    modalChanged = false;
}

void MainWindow::saveAsDataToFile()
{
    setFileNameToSave();
    if(*pathFile!="")
    {
         DATA.writeToFile(*pathFile);
        qDebug()<<"Сохранено: "<<DATA.getSize()<<"авто."<<*pathFile;
        this->setWindowTitle(QString("Курсовая работа по ООП (class CAR) %1").arg(*pathFile));
    }
     else { qDebug()<<"Отсутствует путь для сохранения файла";}

    modalChanged = false;
}

void MainWindow::cellDataChenged(QStandardItem *item)
{
    qDebug()<<"row = "<<item->row()<<"  column = "<<item->column();
    switch(item->column())
    {
    case 0: if(CAR::listModels.contains(item->data(0))){
                DATA[item->row()].setBrand(CAR::listModels.indexOf(item->data(0)));
            }
            else {
            qDebug()<<item->data(0).toString();
                CAR::listModels.append(item->data(0).toString());
                DATA[item->row()].setBrand(CAR::listModels.size()-1);
            }
        break;
    case 1: DATA[item->row()].setYearOfManufacture((item->data(2)).toInt()); break;
    case 2: DATA[item->row()].setPrice((item->data(2)).toInt()); break;
    case 3: DATA[item->row()].setEngineCapacity((item->data(2)).toInt()); break;
    case 4: DATA[item->row()].setPower((item->data(2)).toInt()); break;
    case 5: DATA[item->row()].setMaxSpeed((item->data(2)).toInt()); break;
    case 6: DATA[item->row()].setAcceleration((item->data(2)).toInt()); break;
    case 7: DATA[item->row()].setFuelRate((item->data(2)).toInt()); break;
    case 8: DATA[item->row()].setClearence((item->data(2)).toInt()); break;
    default : break;
    }
    modalChanged = true;
}

void MainWindow::addNewCar()//*************************
{
    addCAR = new QWidget(this,Qt::Window);
    addCAR->setWindowTitle("Добавить новое ТС");
    addCAR->setAttribute(Qt::WA_DeleteOnClose,true);
    addCAR->setWindowModality(Qt::WindowModal);
    addCAR->setFixedSize(400,350);



    QCompleter *completer = new QCompleter(CAR::listModels,addCAR);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    QVBoxLayout  *v_box = new QVBoxLayout(addCAR);
    QVBoxLayout  *h_box = new QVBoxLayout(addCAR);
    QGridLayout *grid_layout = new QGridLayout(addCAR);

    QLabel *brand_label = new QLabel("Марка и модель: ",addCAR);
    QLabel *year_label = new QLabel("Год выпуска: ",addCAR);
    QLabel *price_label = new QLabel("Цена (тыс. руб): ",addCAR);
    QLabel *engine_label = new QLabel("Объем двигателя (см. куб): ",addCAR);
    QLabel *power_label = new QLabel("Мощность (л.с.): ",addCAR);
    QLabel *maxSpeed_label = new QLabel("Максимальная скорость (км/ч): ",addCAR);
    QLabel *acceleration_label = new QLabel("Ускарение (100 км/ч за мс): ",addCAR);
    QLabel *fuelRate_label = new QLabel("Расход топлива (мл): ",addCAR);
    QLabel *clearence_label = new QLabel("Дорожный просвет (мм): ",addCAR);
    QLabel *fotoPath_label = new QLabel("Путь к файлам с ФОТО: ",addCAR);

    QLineEdit *brand_line = new QLineEdit(addCAR);
    brand_line->setCompleter(completer);
    brand_line->setPlaceholderText("на англ.");
    QSpinBox *year_line = new QSpinBox(addCAR);
    year_line->setRange(1995,2025);

    QSpinBox *price_line = new QSpinBox(addCAR);
    price_line->setRange(200,65000);

    QSpinBox *engineCapaciteline = new QSpinBox(addCAR);
    engineCapaciteline->setRange(1200,5000);

    QSpinBox *power_line = new QSpinBox(addCAR);
    power_line->setRange(80,450);

    QSpinBox *maxSpeed_line = new QSpinBox(addCAR);
    maxSpeed_line->setRange(0,500);

    QSpinBox *acceleration_line = new QSpinBox(addCAR);
    acceleration_line->setRange(1000,10000);

    QSpinBox *fuelRate_line = new QSpinBox(addCAR);
    fuelRate_line->setRange(0,65000);

    QSpinBox *clearence_line = new QSpinBox(addCAR);
    clearence_line->setRange(30,1000);

    QPushButton *addFoto = new QPushButton("Добавить ФОТО");
    QObject::connect(addFoto,&QPushButton::clicked,this,&MainWindow::setFileNameFoto);

    QPushButton *createCar = new QPushButton("Создать");
    h_box->addWidget(createCar,Qt::AlignRight);

    QObject::connect(createCar,&QPushButton::clicked,[&,this,brand_line,year_line,price_line,engineCapaciteline,power_line,maxSpeed_line,acceleration_line,fuelRate_line,clearence_line](){
        CAR car;
        brand_line->text();
        if(CAR::listModels.contains(brand_line->text()))
        {
            car.setBrand(static_cast<ushort>(CAR::listModels.indexOf(brand_line->text())));
        }
        else
        {
            CAR::listModels.append(brand_line->text());
            car.setBrand(CAR::listModels.size()-1);
            qDebug()<<"добавлено новая марка ТС!";
        }
        car.setYearOfManufacture(static_cast<ushort>(year_line->value()));
        car.setPrice(static_cast<ushort>(price_line->value()));
        car.setEngineCapacity(static_cast<ushort>(engineCapaciteline->value()));
        car.setPower(static_cast<ushort>(power_line->value()));
        car.setMaxSpeed(static_cast<ushort>(maxSpeed_line->value()));
        car.setAcceleration(static_cast<ushort>(acceleration_line->value()));
        car.setFuelRate(static_cast<ushort>(fuelRate_line->value()));
        car.setClearence(static_cast<ushort>(clearence_line->value()));
        car.picturesPath = *pathFoto;
        pathFoto->clear();
        qDebug()<<"Создана машина!"<<car;
        this->DATA.push_back(car);
        emit this->appearNewCar();
        /*

        */
    });

    grid_layout->addWidget(brand_label,0,0);
    grid_layout->addWidget(brand_line,0,1);
    grid_layout->addWidget(year_label,1,0);
    grid_layout->addWidget(year_line,1,1);
    grid_layout->addWidget(price_label,2,0);
    grid_layout->addWidget(price_line,2,1);
    grid_layout->addWidget(engine_label,3,0);
    grid_layout->addWidget(engineCapaciteline,3,1);
    grid_layout->addWidget(power_label,4,0);
    grid_layout->addWidget(power_line,4,1);
    grid_layout->addWidget(maxSpeed_label,5,0);
    grid_layout->addWidget(maxSpeed_line,5,1);
    grid_layout->addWidget(acceleration_label,6,0);
    grid_layout->addWidget(acceleration_line,6,1);
    grid_layout->addWidget(fuelRate_label,7,0);
    grid_layout->addWidget(fuelRate_line,7,1);
    grid_layout->addWidget(clearence_label,8,0);
    grid_layout->addWidget(clearence_line,8,1);
    grid_layout->addWidget(fotoPath_label,9,0);
    grid_layout->addWidget(addFoto,9,1);
    grid_layout->setHorizontalSpacing(30);
    v_box->addLayout(grid_layout);
    v_box->addLayout(h_box);

    addCAR->setLayout(v_box);
    addCAR->show();

}

void MainWindow::addNewCarToModel()
{
    if(model!=NULL){this->model->clear();}

    qDebug()<<"Загружено: "<<DATA.getSize()<<"авто.";
    if(model==NULL)
    {
        model = new QStandardItemModel(DATA.getSize(),10);
    }
    else
    {
        model->clear();
        model = new QStandardItemModel(DATA.getSize(),10);
    }

    model->setHeaderData(0,Qt::Horizontal,"МАРКА/МОДЕЛЬ");
    model->setHeaderData(1,Qt::Horizontal,"   Год   ");
    model->setHeaderData(2,Qt::Horizontal,"ЦЕНА, руб");
    model->setHeaderData(3,Qt::Horizontal,"ОБЪЕМ ДВ.,\nсм. куб.");
    model->setHeaderData(4,Qt::Horizontal,"МОЩНОСТЬ ДВ.\n л.с.");
    model->setHeaderData(5,Qt::Horizontal,"МАКС. СКОРОСТЬ,\nкм/ч");
    model->setHeaderData(6,Qt::Horizontal,"УСКОРЕНИЕ,\n100 км/ч за n cек.");
    model->setHeaderData(7,Qt::Horizontal,"РАСХОД ТОПЛИВА,\nлит. на 100 км");
    model->setHeaderData(8,Qt::Horizontal,"КЛИРЕНС,\nмм");
    model->setHeaderData(9,Qt::Horizontal,"ФОТО");


    for(int row = 0;row<DATA.getSize();row++)
    {
        for(int col = 0;col<MAX_SPEC;col++)
        {
            model->setItem(row,col,new QStandardItem(DATA[row].getSpecsStr(col)));
            if(col!=0)
            {
                model->item(row,col)->setTextAlignment(Qt::AlignCenter);
                model->item(row,col)->setData(QVariant(DATA[row].getSpecs(SPECIFICATIONS(col))),2);
            }
        }
    }

    tableData->setModel(model);
    tableData->showGrid();
    tableData->setSelectionMode(QAbstractItemView::SingleSelection);
    tableData->setWordWrap(true);

    QHeaderView *horizontalHeader = tableData->horizontalHeader();
    QHeaderView *verticallHeader = tableData->verticalHeader();

    if(true) //
    {
        horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
        verticallHeader->setSectionResizeMode(QHeaderView::Interactive);
        horizontalHeader->setStretchLastSection(true);
        horizontalHeader->setStyleSheet(*styleSheet);
        verticallHeader->setStyleSheet(*styleSheet);
    }
    modalChanged = true;
    QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(cellDataChenged(QStandardItem*)));

}

void MainWindow::deleteCarFromTable()
{
    modalChanged = true;
    QItemSelectionModel *selectionModel = tableData->selectionModel();
    if(selectionModel!=NULL)
    {
        QModelIndex index = selectionModel->currentIndex();
        qDebug()<<"Удаляемая строка "<<index.row();
        if(index.row()>=0)
        {
            this->DATA.erase(index.row());
            this->addNewCarToModel();
        }
    }
}

void MainWindow::createNewTable()
{
    this->DATA.clear();
    this->addNewCarToModel();
    modalChanged = true;
}

void MainWindow::showInfo()
{
    QMessageBox *message = new QMessageBox(QMessageBox::Information,"Общая информация","Велиметов Юсуп Касумович\nПИБ 32з\n2-курс\nPER ASPERA AD ASTRA!",QMessageBox::Ok,this);
    message->show();
}

void MainWindow::printTable()
{
    QPrinter printer;
    printer.setPrinterName("You printer");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected){return;}
    //tableData->render(&printer);
    QTextDocument doc(this);
    doc.setPlainText(DATA[0].prepareToPrint());
    doc.print(&printer);
}

void MainWindow::showFotoOfCar(const QModelIndex &index)
{
    QString pathf;
    int indexCar = index.row();
    int sizeListFotos = DATA[indexCar].picturesPath.size();
    if(sizeListFotos==0){
        pathf = "E:\\Qtprojects\\Kursovay\\Foto\\NoFoto.jpg";
        QPixmap pixMap(pathf);
        lableFoto->setPixmap(pixMap);
        nextFoto->setEnabled(false);
        previosFoto->setEnabled(false);
        indexFoto=0;
    }
    else {
        if(indexFoto>=sizeListFotos)
        {
            nextFoto->setEnabled(false);
            previosFoto->setEnabled(true);
            indexFoto=sizeListFotos-1;
        }
        if(indexFoto<sizeListFotos-1&&indexFoto>0)
        {
            nextFoto->setEnabled(true);
            previosFoto->setEnabled(true);
        }
        if(indexFoto==0&&sizeListFotos>0)
        {
            nextFoto->setEnabled(true);
            previosFoto->setEnabled(false);
        }
        pathf = DATA[indexCar].picturesPath[indexFoto];
        pathf.replace("/","\\");
        QPixmap pixMap(pathf);
        lableFoto->setPixmap(pixMap);
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{

    qDebug()<<"close()";
    if(modalChanged)
    {
        QMessageBox::StandardButton massage;
        massage = QMessageBox::question(this,"Выход:"
                                        ,"Сохранить данные? "
                                        ,QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

        if(massage==QMessageBox::Yes)
        {
            if(*pathFile == "")
            {
                saveAsFileTool->triggered();
            }
            else
            {
                saveFileTool->triggered();
            }

        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete)
    {
        this->deleteCarTool->trigger();
    }
}

