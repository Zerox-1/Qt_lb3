#ifndef FIRSTBILLTHREAD_H
#define FIRSTBILLTHREAD_H

#include <QThread>



class FirstBillThread : public QThread {
    Q_OBJECT
protected:
    void run() override {
        first_bill();
    }
};
#endif // FIRSTBILLTHREAD_H
