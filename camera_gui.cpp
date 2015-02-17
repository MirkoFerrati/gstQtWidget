#include <QApplication>
#include <gst/gst.h>
#include "mainwindow.h"
#include "gstqtMedia.h"
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <QGst/Init>

int main(int argc, char *argv[])
{
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()){
        std::cerr <<"yarpserver not running - run yarpserver"<< std::endl;
        exit(EXIT_FAILURE);
    }
    // yarp network initialization
    yarp.init();
    
    QApplication a(argc, argv);
    QGst::init(&argc, &argv);

    gstqtMedia window;

    window.show();
    return a.exec();
}