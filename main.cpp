/*Created by Maximilian Nebl
 *28.01.2018 Germany
 * This project is for personal use only
 */

#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QXmlSimpleReader>
#include <QTimer>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString myString;
    myString = "\n\nOXTerm - easy OPI Payment Terminal\n\nNetwork Communication Tool v0.1\n\nThis is the first itteration of a new Tool for testing terminals on any OS";
    QLabel *splash = new QLabel(myString);
    splash->setWindowTitle("OXTerm - OPI Payment Terminal Network Communication Tool v0.1");
    splash->resize(300,250);
    splash->show();

    MainWindow w;
    w.setWindowTitle("OXTerm Alpha v0.1 - Skeleton");

    QTimer::singleShot(2500, splash, SLOT(close()));
    QTimer::singleShot(2500, &w, SLOT(show()));  //&dereferenced the MainWindow object



    return app.exec();
}
