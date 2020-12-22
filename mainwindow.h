#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "my_checker.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
private:
    Ui::MainWindow *ui;
    ftc::Checker<int, double>* Checker_id;
    ftc::Checker<std::string, double>* Checker_sd;
    enum VerType{UNKNOW,INT,STRING} vertype;
};
#endif // MAINWINDOW_H
