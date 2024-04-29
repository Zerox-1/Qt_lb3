#include "billworker.h"

#include <qmessagebox.h>

BillWorker::BillWorker(QObject *parent): QObject(parent)
{

}

void BillWorker::first_bill(double billA,double m_totalbalanceA){
    if(billA<0 && abs(billA)>m_totalbalanceA){
        emit ErrorA();
        return;
    }
    m_totalbalanceA+=billA;
}
