#include "saver.h"
#include "windows.h"

#include "mainwindow.h"
#include <QAxObject>
#include <QCoreApplication>
#include <qfile.h>

Saver::Saver()
{

}
void Saver::editFile(double AA,double BB,double VV,double aA,double bB,double vV){
    CoInitializeEx(NULL,COINIT_MULTITHREADED);
    QString str1="D:/Users/Zerox/Documents/QT/BankBill.xlsx";
    QAxObject *excel=new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", str1);

    QAxObject *sheets=workbook->querySubObject("Worksheets");
    QAxObject* sheet=sheets->querySubObject("Item( int )",1);
    QAxObject *usedRange = sheet->querySubObject("UsedRange");
    QAxObject* rows1 = usedRange->querySubObject("Rows");
    int countRows = rows1->property("Count").toInt();
    if(!(aA<0 && abs(aA)>AA)){
        QAxObject* cell=sheet->querySubObject("Cells(int,int)",countRows+1,1);
        QVariant value=cell->dynamicCall("SetValue(const QVariant&)",aA);
        delete cell;;
    }
    if(!(bB<0 && abs(bB)>BB)){
        QAxObject* cell=sheet->querySubObject("Cells(int,int)",countRows+1,2);
        QVariant value=cell->dynamicCall("SetValue(const QVariant&)",bB);
        delete cell;
    }
    if(!(vV<0 && abs(vV)>VV)){
        QAxObject* cell=sheet->querySubObject("Cells(int,int)",countRows+1,3);
        QVariant value=cell->dynamicCall("SetValue(const QVariant&)",vV);
        delete cell;
    }
    workbook->dynamicCall("Save()");
    workbooks->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    delete rows1;
    delete usedRange;
    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    delete excel;
    emit saved();
}
