#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCompleter>
#include <QSpinBox>
#include <QLabel>
#include <QIcon>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include "CAR.h"
#include "VECTOR.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QIcon *icon;
    QString *styleSheet;

    QHBoxLayout *hlayout;

    QTableView *tableData;
    QStandardItemModel *model{NULL};

    QStatusBar *statusBar;

    QToolBar *toolBar;
    QAction *openFileTool;
    QAction *saveFileTool;
    QAction *saveAsFileTool;
    QAction *addTableTool;
    QAction *addCarTool;
    QAction *deleteCarTool;
    QAction *printTool;
    QAction *helpTool;

    QMenuBar *mainMenuBar;

    QMenu *settingMenu;
    QMenu *helpMenu;

    QMenu *fileMenu;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAsFile;
    QAction *exit;

    QString *pathFile;
    QStringList *pathFoto;

    QWidget *addCAR;

    VECTOR<CAR> DATA;
    //CAR *newCAR;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadData();
signals:
private:
   // void closeEvent(QCloseEvent *event) override;
    void setMainMenuBar();
    void setFileMenu();
    void setSettingMenu();
    void setHelpMenu();
    void setTableView();
    void setToolBar();
    void setStatusBar();
    void loadStyleSheet();
    void setFotoPathFilesToCar(CAR&car);
private slots:
    void setFileNameFoto();
    void setFileNameToOpen();
    void setFileNameToSave();
    void loadDataToTable();
    void saveDataToFile();
    void saveAsDataToFile();
    void cellDataChenged(QStandardItem* item);
    void addNewCar();
    void createNewCar();


};
#endif // MAINWINDOW_H
