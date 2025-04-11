#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    pathFile = new QString;

    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowTitle("Курсовая работа по ООП (class CAR)");
    this->resize(600,700);
    this->setFixedWidth(600);

    icon = new QIcon("mainWindowIco.ico");
    this->setWindowIcon(*icon);

    this->setMainMenuBar();

    toolBar = new QToolBar();
    statusBar = new QStatusBar();








    this->setStatusBar(statusBar);
    this->addToolBar(Qt::TopToolBarArea,toolBar);

}

MainWindow::~MainWindow() {}

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
    QObject::connect(openFile,SIGNAL(triggered()),this,SLOT(setFileName()));

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

void MainWindow::setFileName()
{
    *pathFile = QFileDialog::getOpenFileName(this,"Открыть","*.base");
    qDebug()<<*pathFile;
}
/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close()";

}
*/
