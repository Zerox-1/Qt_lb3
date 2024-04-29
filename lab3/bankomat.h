#ifndef BANKOMAT_H
#define BANKOMAT_H

#include <QObject>



class Bankomat: public QObject
{
    Q_OBJECT
public:
    Bankomat();
    void change_balance(double bill,double balance);
signals:
    void finish(double balance);
    void error();
};

#endif // BANKOMAT_H
