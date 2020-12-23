#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QValidator>
#include <QMainWindow>
#include <QFileDialog>
#include <QTabWidget>
#include "my_checker.h"
#include "Graph_Generator.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class TabWidget;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ClickInputButton();
    void ClickCheckButton();
    void ClickStringTypeButton();
    void ClickIntTypeButton();
    void ClickClearLogButton();
    void ClickInputCheckButton();
    void ClickNewCheckerButton();
    void ClickCheckUnicomButton();
    void ClickMinDistButton();
    void ClickSelectPathButton();
    void ClickGenerateButton();
    void ClickClearTextBrowserButton();
private:
    Ui::MainWindow *ui;
    ftc::Checker<int, double>* Checker_id;
    ftc::Checker<std::string, double>* Checker_sd;
    enum VerType{UNKNOW,INT,STRING} vertype;
    zxh::Graph_Generator graphGenerator;
};
#endif // MAINWINDOW_H
