#include "mainwindow.h"

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
    saveFileTool = toolBar->addAction(QIcon("saveIco.ico"),"",QKeySequence("Ctrl+S"));
    saveAsFileTool = toolBar->addAction(QIcon("saveAsIco.ico"),"");
    addTableTool  = toolBar->addAction(QIcon("addTableIco.ico"),"");
    addCarTool = toolBar->addAction(QIcon("addCarIco.ico"),"");
    deleteCarTool = toolBar->addAction(QIcon("deleteCarIco.ico"),"");
    printTool = toolBar->addAction(QIcon("printIco.ico"),"",QKeySequence("Ctrl+P"));
    helpTool = toolBar->addAction(QIcon("helpIco.ico"),"");

    QObject::connect(openFileTool,SIGNAL(triggered()),this,SLOT(setFileNameToOpen()));

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
    qDebug()<<DATA.getSize();
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
    model->setHeaderData(1,Qt::Horizontal,"Год");
    model->setHeaderData(2,Qt::Horizontal,"ЦЕНА");
    model->setHeaderData(3,Qt::Horizontal,"ОБЪЕМ ДВ.");
    model->setHeaderData(4,Qt::Horizontal,"МОЩНОСТЬ ДВ ");
    model->setHeaderData(5,Qt::Horizontal,"МАКС. СКОРОСТЬ");
    model->setHeaderData(6,Qt::Horizontal,"УСКОРЕНИЕ");
    model->setHeaderData(7,Qt::Horizontal,"РАСХОД ТОПЛИВА");
    model->setHeaderData(8,Qt::Horizontal,"КЛИРЕНС");
    model->setHeaderData(9,Qt::Horizontal,"ФОТО");


    for(int row = 0;row<DATA.getSize();row++)
    {
        for(int col = 0;col<MAX_SPEC;col++)
        {
            model->setItem(row,col,new QStandardItem(DATA[row].getSpecsStr(col)));
            //model->item(row,col)->setFlags(Qt::ItemIsEnabled);
        }
    }

    tableData->setModel(model);
    tableData->showGrid();
    tableData->reset();


    QHeaderView *horizontalHeader = tableData->horizontalHeader();
    QHeaderView *verticallHeader = tableData->verticalHeader();

    if(true) //
    {
        horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
        verticallHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
        horizontalHeader->setStretchLastSection(true);
        horizontalHeader->setStyleSheet(*styleSheet);
        verticallHeader->setStyleSheet(*styleSheet);
    }
}
/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close()";

}
*/
