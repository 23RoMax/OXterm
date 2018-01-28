#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

bool loggedIn = false;
bool connectionEst = true;
QString IP;


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
  }
    else {ui->pushButtonLog->setText("Login!");
    logIOError.exec();
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    IP = ui->lineEditIP->text();

    //Create Connection on supplied IP & Port

    connectionEst = true;

    if (connectionEst == true){
        ui->pushButtonLog->setEnabled(true);
        ui->groupBoxConnectivityStatus->setEnabled(true);
        ui->groupBoxRequests->setEnabled(true);
        ui->groupBoxResponse->setEnabled(true);
        ui->textEditConnectionStatus->setText("Connection with: " + IP + " successfull!\n");
    }
    else {ui->pushButtonLog->setEnabled(false);}

}
