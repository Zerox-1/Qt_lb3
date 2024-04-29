#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <qthread.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Saver* saver =new Saver();
    QThread* threadS=new QThread(this);
    saver->moveToThread(threadS);
    connect(this,&MainWindow::startoperation3,saver,&Saver::editFile);


    Bankomat* a=new Bankomat();
    Bankomat* b=new Bankomat();
    Bankomat* v=new Bankomat();
    QThread* threadA=new QThread(this);
    QThread* threadB=new QThread(this);
    QThread* threadV=new QThread(this);

    ui->setupUi(this);
    getBalance();
    m_totalbalanceA=ui->mTotalBill_A->text().toDouble();
    m_totalbalanceB=ui->mTotalBill_B->text().toDouble();
    m_totalbalanceV=ui->mTotalBill_V->text().toDouble();
    connect(qApp,&QCoreApplication::aboutToQuit,this, &MainWindow::saveBalance);
    connect(qApp,&QCoreApplication::aboutToQuit,threadA, &QThread::quit);
    connect(qApp,&QCoreApplication::aboutToQuit,threadB, &QThread::quit);
    connect(qApp,&QCoreApplication::aboutToQuit,threadS, &QThread::quit);
    connect(qApp,&QCoreApplication::aboutToQuit,threadV, &QThread::quit);


    a->moveToThread(threadA);
    connect(this,&MainWindow::startoperation,a,&Bankomat::change_balance);
    connect(a,&Bankomat::finish,this,&MainWindow::getbalance);
    connect(a,&Bankomat::error,this,&MainWindow::errorA);

    b->moveToThread(threadB);
    connect(this,&MainWindow::startoperation1,b,&Bankomat::change_balance);
    connect(b,&Bankomat::finish,this,&MainWindow::getbalance1);
    connect(b,&Bankomat::error,this,&MainWindow::errorB);

    v->moveToThread(threadV);
    connect(this,&MainWindow::startoperation2,v,&Bankomat::change_balance);
    connect(v,&Bankomat::finish,this,&MainWindow::getbalance2);
    connect(v,&Bankomat::error,this,&MainWindow::errorV);

    threadA->start();
    threadB->start();
    threadV->start();
    threadS->start();
}

MainWindow::~MainWindow()
{
    delete threadA;
    delete threadB;
    delete threadV;
    delete threadS;
    delete ui;
}
void MainWindow::errorA(){
    QMessageBox::critical(this,"Critical","Нельзя снять с банкомата А, недостаточно средств!");
}

void MainWindow::errorB(){
    QMessageBox::critical(this,"Critical","Нельзя снять с банкомата Б, недостаточно средств!");
}

void MainWindow::errorV(){
    QMessageBox::critical(this,"Critical","Нельзя снять с банкомата В, недостаточно средств!");
}

void MainWindow::on_pushButton_clicked()
{
    billA=ui->mBill1->text().toDouble();
    billB=ui->mBill2->text().toDouble();
    billV=ui->mBill3->text().toDouble();
    emit startoperation(billA,m_totalbalanceA);
    emit startoperation1(billB,m_totalbalanceB);
    emit startoperation2(billV,m_totalbalanceV);
    emit startoperation3(m_totalbalanceA,m_totalbalanceB,m_totalbalanceV,billA,billB,billV);
}


void MainWindow::on_Historyb_clicked()
{
    history.getFile();
    history.setModal(true);
    history.show();
}

void MainWindow::getBalance(){
    QFile inputFile("D:/Users/Zerox/Documents/QT/lab3/balance.txt");
    QByteArray data;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       data = inputFile.readAll();
       QStringList a=QString(data).split(",",QString::SkipEmptyParts);
       ui->mTotalBill_A->setText(a[0]);
       ui->mTotalBill_B->setText(a[1]);
       ui->mTotalBill_V->setText(a[2]);
       inputFile.close();
    }
}

void MainWindow::saveBalance(){
    QFile file("D:/Users/Zerox/Documents/QT/lab3/balance.txt");
    QByteArray data;
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream *out = new QTextStream(&file);
        *out << ui->mTotalBill_A->text()+QString(",")+ui->mTotalBill_B->text()+QString(",")+ui->mTotalBill_V->text();
        file.close();
    }
}

void MainWindow::getbalance(double balance){
    m_totalbalanceA=balance;
    ui->mTotalBill_A->setText(QString::number(m_totalbalanceA));
}

void MainWindow::getbalance1(double balance){
    m_totalbalanceB=balance;
    ui->mTotalBill_B->setText(QString::number(m_totalbalanceB));
}

void MainWindow::getbalance2(double balance){
    m_totalbalanceV=balance;
    ui->mTotalBill_V->setText(QString::number(m_totalbalanceV));
}
