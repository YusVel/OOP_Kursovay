#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include "CAR.h"
#include "VECTOR.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QIcon icon;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
