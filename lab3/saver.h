#ifndef SAVER_H
#define SAVER_H

#include <QObject>



class Saver: public QObject
{
    Q_OBJECT
public:
    Saver();
    void editFile(double AA,double BB,double VV,double aA,double bB,double vV);
signals:
    void saved();
};

#endif // SAVER_H
