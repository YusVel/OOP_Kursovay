#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    icon.addFile("mainWindowIco.ico");
    this->setWindowIcon(icon);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowTitle("Курсовая работа по ООП (class CAR)");
    this->resize(600,700);
    this->setFixedWidth(600);

}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close()";

}
