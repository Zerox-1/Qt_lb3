#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bankomat.h"
#include "billworker.h"
#include "saver.h"

#include <QMainWindow>
#include <history.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getBalance();
    void saveBalance();

private slots:
    void on_pushButton_clicked();
    void on_Historyb_clicked();

    void getbalance(double balance);
    void getbalance1(double balance);
    void getbalance2(double balance);

    void errorA();
    void errorB();
    void errorV();

private:
    Ui::MainWindow *ui;
    History history;
    Bankomat a;
    Bankomat b;
    Bankomat v;
    QThread *threadA ;
    QThread *threadB;
    QThread *threadV ;
    Saver *saver;
    QThread *threadS;
    double m_totalbalanceA;
    double m_totalbalanceB;
    double m_totalbalanceV;
    double billA;
    double billB;
    double billV;
signals:
    void startoperation(double bill,double balance);
    void startoperation1(double bill,double balance);
    void startoperation2(double bill,double balance);
    void startoperation3(double AA,double BB,double VV,double aA,double bB,double vV);
};
#endif // MAINWINDOW_H
