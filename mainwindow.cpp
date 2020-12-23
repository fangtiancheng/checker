#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_checker.h"
#define debug printf("in mw.cpp line %d\n",__LINE__);

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
    connect(ui->CheckUnicomButton,SIGNAL(clicked()),this,SLOT(ClickCheckUnicomButton()));
    connect(ui->CheckMinDistButton,SIGNAL(clicked()),this,SLOT(ClickMinDistButton()));
    connect(ui->SelectPathButton,SIGNAL(clicked()),this,SLOT(ClickSelectPathButton()));
    connect(ui->GenerateButton,SIGNAL(clicked()),this,SLOT(ClickGenerateButton()));
    connect(ui->ClearTextBrowserButton,SIGNAL(clicked()),this,SLOT(ClickClearTextBrowserButton()));
    ui->VerNumInput->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->EdgeNumInput->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->BlockNumInput->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    debug
    graphGenerator = new zxh::Graph_Generator();
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
    if(this->graphGenerator != NULL){
        delete this->graphGenerator;
        graphGenerator = NULL;
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
            this->Checker_id = NULL;
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
            this->Checker_sd = NULL;
        }
        try{
            this->Checker_sd = new ftc::Checker<std::string, double>(ui->InputGraph->toPlainText().toStdString());
            ui->LogBrowser->append(QString("total weight = ") + QString::number(Checker_sd->get_total_weight(),'f',4));
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
void MainWindow::ClickCheckUnicomButton(){
    switch(this->vertype){
    case VerType::INT:{
        if(this->Checker_id == NULL){
            ui->LogBrowser->append(QString("Havn't New Checker"));
            break;
        }
        try{
            bool ok1,ok2;
            int ver1 = ui->Ver1Input->toPlainText().toInt(&ok1);
            int ver2 = ui->Ver2Input->toPlainText().toInt(&ok2);
            if(!ok1||!ok2){
                throw ftc::Error(__LINE__,"ver format error");
            }
            bool is_unicom = this->Checker_id->unicom(ver1, ver2);
            if(is_unicom) ui->LogBrowser->append(QString::number(ver1) + " is connected to "+QString::number(ver2));
            else ui->LogBrowser->append(QString::number(ver1) + " is not connected to "+QString::number(ver2));
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
            QString ver1 = ui->Ver1Input->toPlainText();
            QString ver2 = ui->Ver2Input->toPlainText();
            bool is_unicom = this->Checker_sd->unicom(ver1.toStdString(), ver2.toStdString());
            if(is_unicom) ui->LogBrowser->append(ver1 + " is connected to "+ver2);
            else ui->LogBrowser->append(ver1 + " is not connected to "+ ver2);
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
void MainWindow::ClickMinDistButton(){
    switch(this->vertype){
    case VerType::INT:{
        if(this->Checker_id == NULL){
            ui->LogBrowser->append(QString("Havn't New Checker"));
            break;
        }
        try{
            bool ok1,ok2;
            int ver1 = ui->Ver1Input->toPlainText().toInt(&ok1);
            int ver2 = ui->Ver2Input->toPlainText().toInt(&ok2);
            if(!ok1||!ok2){
                throw ftc::Error(__LINE__,"ver format error");
            }
            double min_dist = this->Checker_id->min_dist(ver1, ver2);
            ui->LogBrowser->append("min dist between " + QString::number(ver1) + " and "+QString::number(ver2)+" is "+QString::number(min_dist, 'f',4));
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
            QString ver1 = ui->Ver1Input->toPlainText();
            QString ver2 = ui->Ver2Input->toPlainText();
            double min_dist = this->Checker_sd->min_dist(ver1.toStdString(), ver2.toStdString());
            ui->LogBrowser->append("min dist between " + ver1 + " and "+ ver2 +" is "+QString::number(min_dist, 'f',4));
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
void MainWindow::ClickSelectPathButton(){
    QString fileName = QFileDialog::getOpenFileName
            (0, QString(), QString(),tr("*.*"));
    ui->InputLocation->setText(fileName);
}
void MainWindow::ClickGenerateButton(){
    QString filename = ui->InputLocation->toPlainText();
    zxh::WORKING_STATE wkstt = zxh::WORKING_STATE::UNKNOWN;
    QString ModeLog;
    if(ui->AddModeButton->isChecked()){
        if(wkstt != zxh::WORKING_STATE::APPEND_MODE){
            wkstt = zxh::WORKING_STATE::APPEND_MODE;
            // ui->textBrowser->append(QString("choose Append Mode"));
            ModeLog += QString("Mode = Append; ");
        }
    }
    else if(ui->MultyConnectButton->isChecked()){
        if(wkstt != zxh::WORKING_STATE::MULTIBLOCK_MODE){
            wkstt = zxh::WORKING_STATE::MULTIBLOCK_MODE;
            // ui->textBrowser->append(QString("choose Multy Block Mode"));
            ModeLog += QString("Mode = Multy Block; ");
        }
    }
    else if(ui->NormalModeButton->isChecked()){
        if(wkstt != zxh::WORKING_STATE::RANDOM_MODE){
            wkstt = zxh::WORKING_STATE::RANDOM_MODE;
            // ui->textBrowser->append(QString("choose Normal Mode"));
            ModeLog += QString("Mode = Normal; ");
        }
    }
    else if(ui->OneConnectModeButton->isChecked()){
        if(wkstt != zxh::WORKING_STATE::SINGALBLOCK_MODE){
            wkstt = zxh::WORKING_STATE::SINGALBLOCK_MODE;
            // ui->textBrowser->append(QString("choose Single Block Mode"));
            ModeLog += QString("Mode = Single Block; ");
        }
    }
    else{
        ui->textBrowser->append(QString("Havn't choose mode yet"));
        return;
    }
    bool ok_n = true, ok_m = true, ok_b = true;
    int n = 0, m = 0, numOfBlock = 0;
    if(wkstt != zxh::WORKING_STATE::APPEND_MODE)
        n = ui->VerNumInput->text().toInt(&ok_n);
    m = ui->EdgeNumInput->text().toInt(&ok_m);
    if(wkstt == zxh::WORKING_STATE::MULTIBLOCK_MODE)
        numOfBlock = ui->BlockNumInput->text().toInt(&ok_b);
    if(!ok_n||!ok_m||!ok_b){
        ui->textBrowser->append(QString("input number error"));
        return;
    }
    bool NoSelfLoop = ui->NoSelfLoopButton->isChecked();
    bool NoMultyEdge = ui->NoMultyEdgeButton->isChecked();
    if(NoSelfLoop){
        ModeLog += QString("Self Loop = off; ");
    }
    else{
        ModeLog += QString("Self Loop = on; ");
    }
    if(NoMultyEdge){
        ModeLog += QString("Multy Edge = off; ");
    }
    else{
        ModeLog += QString("Multy Edge = on; ");
    }
    try{
        graphGenerator->generate(wkstt, filename.toStdString().c_str(), n, m, numOfBlock,!NoSelfLoop, !NoMultyEdge);
        ui->textBrowser->append(ModeLog);
        ui->textBrowser->append(QString("successfully generate a graph!"));
    }
    catch(ftc::Error e){
        ui->textBrowser->append(QString::fromStdString(e.message));
    }
}
void MainWindow::ClickClearTextBrowserButton(){
    ui->textBrowser->clear();
}
#undef debug
