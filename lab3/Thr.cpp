#include "Thr.h"

Thr::Thr(QObject *parent): QObject(parent)
{
}
void Thr::first_bill(double billA,double m_totalbalanceA){
    if(billA<0 && abs(billA)>m_totalbalanceA){
//        QMessageBox::critical(this,"Critical","Нельзя снять с банкомата А, недостаточно средств!");
        return;
    }
    m_totalbalanceA+=billA;
    emit Finished(m_totalbalanceA);
}
