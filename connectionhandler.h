#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#endif // CONNECTIONHANDLER_H

#include <QString>
#include "mainwindow.h"
#include <QObject>

class TCP : public QObject
{

public:
    QString transmit(QString const& IP, QString const& port, QString const& opi_payload);
    QString connection(QString const& IP, QString const& port, QString const& opi_payload);
    QString logIO(QString const& IP, QString const& port, QString const& opi_payload);

public slots:
    void setResult(QString status);

signals:
    void textChanged(QString);
};
