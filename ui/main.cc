#include <QGuiApplication>
#include "LIMoSim/sim/simulation.h"
#include "ui/uimanager.h"
#include "LIMoSim/location/position.h"

#include <QFile>
#include <QDebug>
#include <QDebug>

using namespace LIMoSim;

#include "LIMoSim/settings/filehandler.h"
#include "LIMoSim/settings/xmlparser.h"


#include "LIMoSim/sim/rng.h"

#include "ui/plot/box.h"
#include "ui/qteventscheduler.h"

#include <iostream>


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(msg!="QTransform::translate with NaN called")
        std::cout << msg.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    qDebug() << argc;

    qInstallMessageHandler(myMessageOutput);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtEventScheduler scheduler;
    Simulation *sim = Simulation::getInstance(&scheduler);



    std::string dir = "D:/QtProjects/LIMoSim/resources/";
    dir = "C:/Users/Benjamin/Desktop/LIMoSim_dev/resources/";
    //dir = "/home/sliwa/inet/inet/src/inet/LIMoSim/resources/";

    sim->load(dir + "TUDO.osm", dir + "Cars.xml");



    UiManager *ui = UiManager::getInstance();


    return app.exec();
}
