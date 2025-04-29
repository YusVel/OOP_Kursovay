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
#include <QTextEdit>
#include <QIcon>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QMessageBox>
#include <QModelIndex>
#include <QKeyEvent>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include "CAR.h"
#include "VECTOR.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QIcon *icon;
    QString *styleSheet;

    QLabel *lableFoto;
    QPushButton *nextFoto;
    QPushButton *previosFoto;

    QTextEdit *textEdit;

    QPushButton *addNewFoto;
    QPushButton *changeListFoto;
    QPushButton *deleteFoto;

    QVBoxLayout *vlayout;

    QTableView *tableData;
    QStandardItemModel *model{NULL};
    bool modalChanged = false;

    QStatusBar *statusBar;

    QToolBar *toolBar;
    QAction *openFileTool;
    QAction *saveFileTool;
    QAction *saveAsFileTool;
    QAction *addTableTool;
    QAction *addCarTool;
    QAction *deleteCarTool;
    QAction *increaseTool;
    QAction *decreaseTool;
    QAction *printTool;
    QLineEdit *searchLine;
    QAction *helpTool;

    QMenuBar *mainMenuBar;

    QMenu *settingMenu;

    QMenu *fileMenu;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAsFile;
    QAction *exit;

    QString *pathFile;
    QStringList *pathFoto;

    QWidget *addCAR;

    VECTOR<CAR> DATA;
    ushort indexFoto{0};
    //CAR *newCAR;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void appearNewCar();
protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void setMainMenuBar();
    void setFileMenu();
    void setSettingMenu();
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
    void addNewCarToModel();
    void deleteCarFromTable();
    void createNewTable();
    void showInfo();
    void printTable();
    void showFotoOfCar(const QModelIndex &index);
    void sortIncrease();
    void sortDecrease();
    void deleteFotoOfCar();
    void addFotoOfCar();
    void changeFotosOfCar();
    void searchForNameOfBrandOnLineEdite(const QString &text);
};
#endif // MAINWINDOW_H
