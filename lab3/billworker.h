#ifndef BILLWORKER_H
#define BILLWORKER_H

#include <QObject>



class BillWorker: public QObject
{
    Q_OBJECT
public:
    void first_bill(double billA, double m_totalbalanceA);
    BillWorker(QObject *parent);
signals:
    void ErrorA();
};

#endif // BILLWORKER_H
