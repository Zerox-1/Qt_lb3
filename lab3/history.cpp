#include "history.h"
#include <windows.h>

#include "ui_history.h"

#include <qaxobject.h>

QString str="D:/Users/Zerox/Documents/QT/BankBill.xlsx";
History::History(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
}

History::~History()
{
    delete ui;
}

void History::getFile(){
    CoInitializeEx(NULL,COINIT_MULTITHREADED);
    ui->tableWidget->clear();
    QAxObject* excel =new QAxObject("Excel.Application",0);
    QAxObject* workbooks=excel->querySubObject("Workbooks");
    QAxObject* workbook=workbooks->querySubObject("Open(const QString",str);
    QAxObject* sheets = workbook->querySubObject("Worksheets");
    QAxObject* sheet = sheets->querySubObject("Item(int",1);
    QAxObject* usedRange = sheet->querySubObject("UsedRange");
    QAxObject* rows = usedRange->querySubObject("Rows");
    int countRows = rows->property("Count").toInt();
    const int e=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(countRows);
    for ( int row = 0; row < countRows+1; row++ ){
        for ( int column = 0; column < 3; column++ ){
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", row + 1, column + 1);
            QVariant value = cell->property("Value");
            QTableWidgetItem* item = new QTableWidgetItem(value.toString());
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(row, column, item);
            delete cell;
        }
    }
    delete rows;
    delete usedRange;
    delete sheet;
    delete sheets;
    workbook->dynamicCall("Close()");
    workbook->clear();
    delete workbook;
    delete workbooks;
    delete excel;
}
