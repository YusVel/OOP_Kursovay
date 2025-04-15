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

    hlayout = new QHBoxLayout();
    hlayout->addWidget(tableData);
    hlayout->setAlignment(Qt::AlignBottom);
    hlayout->setGeometry(QRect(10,55,1030,300));

    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowTitle("Курсовая работа по ООП (class CAR)");
    this->resize(600,700);
    this->setFixedWidth(1050);

    icon = new QIcon("mainWindowIco.ico");
    this->setWindowIcon(*icon);

}

MainWindow::~MainWindow() {}

void MainWindow::loadData()
{

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
    fileMenu = new QMenu(tr("Файл"),mainMenuBar);
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
    settingMenu = new QMenu(tr("Настройки"),mainMenuBar);

    mainMenuBar->addMenu(settingMenu);
}

void MainWindow::setHelpMenu()
{
    helpMenu = new QMenu(tr("Справка"),mainMenuBar);

    mainMenuBar->addMenu(helpMenu);
}

void MainWindow::setTableView()
{
    tableData = new QTableView(this);
    tableData->setStyleSheet(*styleSheet);
}

void MainWindow::setToolBar()
{
    toolBar = new QToolBar();
    toolBar->setMovable(false);
    openFileTool = toolBar->addAction(QIcon("openFileIco.ico"),"",QKeySequence("Ctrl+O"));
    openFileTool->setToolTip("Открыть");
    saveFileTool = toolBar->addAction(QIcon("saveIco.ico"),"",QKeySequence("Ctrl+S"));
    saveFileTool->setToolTip("Сохранить");
    saveAsFileTool = toolBar->addAction(QIcon("saveAsIco.ico"),"");
    saveAsFileTool->setToolTip("Сохранить как");
    addTableTool  = toolBar->addAction(QIcon("addTableIco.ico"),"");
    addTableTool->setToolTip("Создать новую таблицу");
    addCarTool = toolBar->addAction(QIcon("addCarIco.ico"),"");
    addCarTool->setToolTip("Добавить новое ТС");
    deleteCarTool = toolBar->addAction(QIcon("deleteCarIco.ico"),"");
    deleteCarTool->setToolTip("Удалить");
    printTool = toolBar->addAction(QIcon("printIco.ico"),"",QKeySequence("Ctrl+P"));
    printTool->setToolTip("Печать");
    helpTool = toolBar->addAction(QIcon("helpIco.ico"),"");
    helpTool->setToolTip("Справка");

    QObject::connect(openFileTool,SIGNAL(triggered()),this,SLOT(setFileNameToOpen()));
    QObject::connect(saveFileTool,SIGNAL(triggered()),this,SLOT(saveDataToFile()));
    QObject::connect(saveAsFileTool,SIGNAL(triggered()),this,SLOT(saveAsDataToFile()));
    QObject::connect(addCarTool,SIGNAL(triggered()),this,SLOT(addNewCar()));

    this->addToolBar(Qt::TopToolBarArea,toolBar);
}

void MainWindow::setStatusBar()
{
    statusBar = new QStatusBar();
    this->QMainWindow::setStatusBar(statusBar);
}

void MainWindow::loadStyleSheet()
{
    QFile file("styleSheet.txt");
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
    loadDataToTable();
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
        delete model;
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
    DATA.writeToFile(*pathFile);
    qDebug()<<"Сохранено: "<<DATA.getSize()<<"авто."<<*pathFile;
}

void MainWindow::saveAsDataToFile()
{
    setFileNameToSave();
    DATA.writeToFile(*pathFile);
    qDebug()<<"Сохранено: "<<DATA.getSize()<<"авто."<<*pathFile;
    this->setWindowTitle(QString("Курсовая работа по ООП (class CAR) %1").arg(*pathFile));
}

void MainWindow::cellDataChenged(QStandardItem *item)
{
    qDebug()<<"row = "<<item->row()<<"  column = "<<item->column();
    switch(item->column())
    {
    case 0: DATA[item->row()].setBrand((item->data(2)).toInt()); break;
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

void MainWindow::createNewCar()
{

}


/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close()";

}
*/
