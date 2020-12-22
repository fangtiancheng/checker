#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_checker.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Checker_id = NULL;
    this->Checker_sd = NULL;
    connect(ui->CheckButton,SIGNAL(clicked()),this,SLOT(ClickCheckButton()));
    connect(ui->InputGraphButton,SIGNAL(clicked()),this,SLOT(ClickInputButton()));
    connect(ui->InputSubGraphButton,SIGNAL(clicked()),this,SLOT(ClickInputCheckButton()));
    connect(ui->StringFormatButton,SIGNAL(clicked()),this,SLOT(ClickStringTypeButton()));
    connect(ui->IntFormatButton,SIGNAL(clicked()),this,SLOT(ClickIntTypeButton()));
    connect(ui->ClearLogButton,SIGNAL(clicked()),this,SLOT(ClickClearLogButton()));
    connect(ui->NewCheckerButton,SIGNAL(clicked()),this,SLOT(ClickNewCheckerButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(this->Checker_id!=NULL){
        delete this->Checker_id;
        this->Checker_id = NULL;
    }
    if(this->Checker_sd!=NULL){
        delete this->Checker_sd;
        this->Checker_sd = NULL;
    }
}

void MainWindow::ClickCheckButton(){
    switch(this->vertype){
    case VerType::INT:{
        if(this->Checker_id == NULL){
            ui->LogBrowser->append(QString("Havn't New Checker"));
            break;
        }
        try{
            std::string output = this->Checker_id->check(ui->InputSubGraph->toPlainText().toStdString());
            ui->LogBrowser->append(QString::fromStdString(output));
        }
        catch(ftc::Error e){
            ui->LogBrowser->append(QString::fromStdString(e.message));
        }

    }break;
    case VerType::STRING:{
        if(this->Checker_sd==NULL){
            ui->LogBrowser->append(QString("Havn't New Checker"));
            break;
        }
        try{
            std::string output = this->Checker_sd->check(ui->InputSubGraph->toPlainText().toStdString());
            ui->LogBrowser->append(QString::fromStdString(output));
        }
        catch(ftc::Error e){
            ui->LogBrowser->append(QString::fromStdString(e.message));
        }
    }
        break;
    default:
        ui->LogBrowser->append(QString("Ver Type Unknow!"));
        break;
    }
}

void MainWindow::ClickIntTypeButton(){
    if(this->vertype == VerType::INT) return;
    this->vertype = VerType::INT;
    ui->LogBrowser->append(QString("set Ver Type: int"));
    delete this->Checker_sd;
    this->Checker_sd = NULL;
}
void MainWindow::ClickStringTypeButton(){
    if(this->vertype == VerType::STRING) return;
    this->vertype = VerType::STRING;
    ui->LogBrowser->append(QString("set Ver Type: string"));
    delete this->Checker_id;
    this->Checker_id = NULL;
}
void MainWindow::ClickClearLogButton(){
    ui->LogBrowser->setText(QString());
}
void MainWindow::ClickInputButton()
{
    QString fileName = QFileDialog::getOpenFileName
            (0, QString(), QString(),tr("text (*.txt *.log)"));
    ui->InputGraph->setText(fileName);
}
void MainWindow::ClickInputCheckButton(){
    QString fileName = QFileDialog::getOpenFileName
            (0, QString(), QString(),tr("text (*.txt *.log)"));
    ui->InputSubGraph->setText(fileName);
}
void MainWindow::ClickNewCheckerButton(){
    switch(this->vertype){
    case VerType::INT:{
        if(this->Checker_id != NULL){
            delete this->Checker_id;
        }
        try{
            this->Checker_id = new ftc::Checker<int, double>(ui->InputGraph->toPlainText().toStdString());
            ui->LogBrowser->append(QString("total weight = ") + QString::number(Checker_id->get_total_weight(),'f',4));
        }
        catch(ftc::Error e){
            ui->LogBrowser->append(QString::fromStdString(e.message));
        }

    }break;
    case VerType::STRING:{
        if(this->Checker_sd!=NULL){
            delete this->Checker_sd;
        }
        try{
            this->Checker_sd = new ftc::Checker<std::string, double>(ui->InputGraph->toPlainText().toStdString());
            ui->LogBrowser->append(QString("total weight = ") + QString::number(Checker_id->get_total_weight(),'f',4));
        }
        catch(ftc::Error e){
            ui->LogBrowser->append(QString::fromStdString(e.message));
        }
    }
        break;
    default:
        ui->LogBrowser->append(QString("Ver Type Unknow!"));
        break;
    }
}
