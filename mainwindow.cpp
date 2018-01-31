/*Created by Maximilian Nebl
 *28.01.2018 Germany
 * This project is for personal use only
 *
 * To-Do's:
 *
 * - remove the logic that repeats in every function and create classes
 * - get OPI specification for creating proper XML
 * - parse XML properly to pretty print the values not the xml
 * - add Port & IP Scanner for multiple OS
 * - keep on making this multi OS supported
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionhandler.h"
#include <QMessageBox>
#include <QString>
#include <QXmlStreamReader>
#include <QTimer>
#include <QTcpSocket>
#include <QAbstractSocket>

bool loggedIn = false;
bool connectionEst = true;
QString IP;
QString port;
QTcpSocket socket;
QString XMLreversal = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> <CardServiceRequest ApplicationSender=\"OXterm\" POPID=\"001\" RequestID=\"0\" RequestType=\"PaymentReversal\" WorkstationID=\"1\"> <POSdata><POSTimeStamp>2018-01-28T21:37:06</POSTimeStamp></POSdata> <OriginalTransaction STAN=\"\" TerminalBatch=\"0000000000\"  TerminalID=\"\"/></CardServiceRequest>";
QString XMLprint = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?><CardServiceRequest ApplicationSender=\"WINPOS\" POPID=\"001\" RequestID=\"0\" RequestType=\"TicketReprint\" WorkstationID=\"1\"> <POSdata><POSTimeStamp>2018-01-28T21:39:59</POSTimeStamp></POSdata> </CardServiceRequest>";
QString XMLpretty;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonLog->setText("Login!"); //Initiate Login Button on startup
    ui->pushButtonLog->setEnabled(false);
    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonDiagnose->setEnabled(false);
    ui->groupBoxPayment->setEnabled(false);
    ui->groupBoxRequests->setEnabled(false);
    ui->groupBoxResponse->setEnabled(false);
    ui->groupBoxConnectivityStatus->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLog_clicked()
{

    QMessageBox logIOError;
    logIOError.setText("Login not possible; \nEither you are already logged in, or Login fails!");

    if (loggedIn == false) {
        ui->pushButtonLog->setText("Logout!");
        //call login function
        //if login succesfull set logged_in == true
        loggedIn = true;
        ui->groupBoxPayment->setEnabled(true);
        ui->textEditConnectionStatus->setText("Log In on: " + IP + " successfull!\n");
        ui->pushButtonCancel->setEnabled(true);
        ui->pushButtonDiagnose->setEnabled(true);
  }
    else {ui->pushButtonLog->setText("Login!");
    logIOError.exec();
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    TCP *temp;
    temp = new TCP;
    QString status;
    QString connectXML;
    QString response;
    connectXML = "This should be the connection establishment XML for the Terminal";
    IP = ui->lineEditIP->text();
    port = ui->lineEditPorts->text();
    response = temp->connection(IP, port, connectXML);
    connect(temp, SIGNAL(textChanged(QString)), ui->textEditConnectionStatus, SLOT(setText(QString)));

    ui->textEditResponseVerbose->setText(response);
    ui->textEditResponsePretty->setText(response);

//    socket.connectToHost(IP, port.toInt(), QIODevice::ReadWrite); //establishing connection with server
//    socket.waitForConnected();
//    bool connected = socket.state();
//    if (connected == true) {
//        status = "Connection established with: " + IP +"!\n";
//        socket.write(connectXML.toLocal8Bit());}
//    else {status = "Connection with: " + IP +" failed!\n";}
//    socket.write(connectXML.toLocal8Bit());

    //Create Connection on supplied IP & Port
    bool connected = true;

    if (connected == true){
        ui->pushButtonLog->setEnabled(true);
        ui->groupBoxConnectivityStatus->setEnabled(true);
        ui->groupBoxRequests->setEnabled(true);
        ui->groupBoxResponse->setEnabled(true);
        //ui->textEditConnectionStatus->setText("Connection with: " + IP + " successfull!\n");
    }
    else {ui->pushButtonLog->setEnabled(false);}

}

void MainWindow::on_pushButtonDiagnose_clicked()
{
    QString status;
    QString connectXML;
    connectXML = "This should be the connection establishment XML for the Terminal";
    IP = ui->lineEditIP->text();
    port = ui->lineEditPorts->text();
    socket.connectToHost(IP, port.toInt(), QIODevice::ReadOnly); //establishing connection with server
    socket.waitForConnected();
    bool connected = socket.state();
    if (connected == true) {
        status = "Connection established with: " + IP +"!\n";
        socket.write(connectXML.toLocal8Bit());}
    else {status = "Connection with: " + IP +" failed!\n";}

    QByteArray data = socket.readAll();
    QString answer2 = QString::fromUtf8(data);
    ui->textEditConnectionStatus->setText(status);
    ui->textEditResponseVerbose->setText(answer2);
    ui->textEditResponsePretty->setText(answer2);
    //Create Connection on supplied IP & Port

}


void MainWindow::on_pushButtonRefund_clicked()
{
    QString status;
    IP = ui->lineEditIP->text();
    port = ui->lineEditPorts->text();
    socket.connectToHost(IP, port.toInt(), QIODevice::ReadWrite); //establishing connection with server
    socket.waitForConnected();
    bool connected = socket.state();
    if (connected == true) {
        status = "Connection established with: " + IP +"!\n";
        socket.write(XMLreversal.toLocal8Bit());}
    else {status = "Connection with: " + IP +" failed!\n";}

    QByteArray data = socket.readAll();
    QString answer = QString::fromUtf8(data);

    QXmlStreamReader reader(XMLreversal);
    QXmlStreamWriter writer(&XMLpretty);
    writer.setAutoFormatting(true);

    while (!reader.atEnd()) {
        reader.readNext();
        if (!reader.isWhitespace()) {
            writer.writeCurrentToken(reader);
        }
    }

    ui->textEditConnectionStatus->setText(status);
    ui->textEditRequests->setText(XMLreversal);
    ui->textEditResponseVerbose->setText(answer);
    ui->textEditResponsePretty->setText(XMLpretty);

}
