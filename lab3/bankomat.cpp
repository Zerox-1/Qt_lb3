#include "bankomat.h"
#include <QtMath>

Bankomat::Bankomat(){}

void Bankomat::change_balance(double bill,double balance){
    if(bill<0 && abs(bill)>balance){
//        QMessageBox::critical(this,"Critical","Нельзя снять с банкомата А, недостаточно средств!");
        emit error();
        return ;
    }
    balance+=bill;
    emit finish(balance);
}
