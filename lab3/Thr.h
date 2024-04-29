#ifndef THREAD_H
#define THREAD_H

#include <QObject>



class Thr: public QObject
{
    Q_OBJECT
public:
    Thr(QObject *parent = nullptr);
    void first_bill(double billA,double m_totalbalanceA);
signals:
    void Finished(double);
};

#endif // THREAD_H
