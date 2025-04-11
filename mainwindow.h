#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QFileDialog>
#include <QString>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include "CAR.h"
#include "VECTOR.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QIcon *icon;

    QStatusBar *statusBar;
    QToolBar *toolBar;
    QMenuBar *mainMenuBar;
    QMenu *fileMenu;
    QMenu *settingMenu;
    QMenu *helpMenu;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAsFile;
    QAction *exit;

    QString *pathFile;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
   // void closeEvent(QCloseEvent *event) override;
    void setMainMenuBar();
    void setFileMenu();
    void setSettingMenu();
    void setHelpMenu();
private slots:
    void setFileName();

};
#endif // MAINWINDOW_H
