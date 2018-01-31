#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionhandler.h"
#include <QMessageBox>
#include <QString>
#include <QXmlStreamReader>
#include <QTimer>
#include <QTcpSocket>
#include <QAbstractSocket>

QString connection(QString const& IP, QString const& port, QString const& opi_payload)
{
    QString connectXML = opi_payload;
    QTcpSocket socket;
    QString status;
    QByteArray data;
    QString response;

    socket.connectToHost(IP, port.toInt(), QIODevice::ReadWrite); //establishing connection with server
    socket.waitForConnected();
    bool connected = socket.state();
    if (connected == true) {
        status = "Connection established with: " + IP +"!\nSending payload!";
        socket.write(connectXML.toLocal8Bit());
        data = socket.readAll();
        response = QString::fromUtf8(data);
    }
    else {status = "Connection with: " + IP +" failed!\n";}
    emit textChanged(status);

    return response;
}
