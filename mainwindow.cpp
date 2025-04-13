#include "mainwindow.h"
#include <qwindowdefs.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{

    pathFile = new QString;
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
    QWidget *addCAR = new QWidget(this,Qt::Window);
    addCAR->setWindowTitle("Добавить новое ТС");
    addCAR->setAttribute(Qt::WA_DeleteOnClose,true);
    addCAR->setWindowModality(Qt::WindowModal);
    addCAR->resize(400,500);
    QGridLayout *grid_layout = new QGridLayout(addCAR);
    QLabel *brand_label = new QLabel("Марка и модель: ");
    QLabel year_label("Год выпуска: ");
    QLabel price_label("Цена: ");
    QLabel engine_label("Объем двигателя: ");
    QLabel power_label("Мощность: ");
    QLabel maxSpeed_label("Максимальная скорость: ");
    QLabel acceleration_label("Ускарение: ");
    QLabel fuelRate_label("Марка и модель: ");
    QLabel clearence_label("Марка и модель: ");
    QLineEdit brand_line;
    QLineEdit year_line;
    year_line.setPlaceholderText("год от рождества");
    QLineEdit price_line;
    price_line.setPlaceholderText("х1000 рублей");
    QLineEdit engineCapaciteline;
    engineCapaciteline.setPlaceholderText("в куб. сантиметрах");
    QLineEdit power_line;
    power_line.setPlaceholderText("в лошадиных силах");
    QLineEdit maxSpeed_line;
    maxSpeed_line.setPlaceholderText(" в км/ч");
    QLineEdit acceleration_line;
    acceleration_line.setPlaceholderText("в милисекундах");
    QLineEdit fuelRate_line;
    fuelRate_line.setPlaceholderText("в милилитрах");
    QLineEdit clearence_line;
    clearence_line.setPlaceholderText("в милиметрах");


    grid_layout->addWidget(brand_label,0,0,30,Qt::AlignRight);
    addCAR->setLayout(grid_layout);
    addCAR->show();
}


/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close()";

}
*/
