#include "firstbillthread.h"

FirstBillThread::FirstBillThread(QObject *parent) : QThread(parent) {}

void FirstBillThread::run()
{
    if(billA < 0 && abs(billA) > m_totalbalanceA)
    {
        emit criticalMessage("Нельзя снять с банкомата А, недостаточно средств!");
        return;
    }
    m_totalbalanceA += billA;
}
