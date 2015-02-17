#include <QApplication>
#include <gst/gst.h>
// #include "streaming_window.h"
#include "mainwindow.h"
extern "C"
{
    #include <gst/interfaces/xoverlay.h>
}
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>

void addVideo(int port, WId id)
{
    GstElement *bin = gst_pipeline_new ("pipeline");
    g_assert(bin);

    GstElement *testSrc = gst_element_factory_make("udpsrc", "source");
    g_assert(testSrc);

    //To receive gst-launch udpsrc port=1234 ! jpegdec ! xvimagesink sync=false
    
    
    g_object_set (G_OBJECT (testSrc), "port", port, NULL);
//     g_object_set (G_OBJECT (testSrc), "caps",
//             gst_caps_new_simple ("application/x-rtp",
//                          "payload", G_TYPE_INT, 127,
//                          NULL), NULL);

//     GstElement *depay = gst_element_factory_make("rtph264depay", "depay");
//     g_assert(depay);
//     GstElement *h264 = gst_element_factory_make("ffdec_h264", "h264");
//     g_assert(h264);
    GstElement *decoder = gst_element_factory_make("jpegdec", "decoder");
    g_assert(decoder);
    
    GstElement *videoOut = gst_element_factory_make("xvimagesink", "video out");
    g_assert(videoOut);
    
    gst_bin_add_many(GST_BIN(bin), testSrc,decoder, videoOut, NULL);
    gst_element_link_many (testSrc, decoder,videoOut,NULL);
    gst_element_set_state(GST_ELEMENT(bin), GST_STATE_PLAYING);
    gst_x_overlay_set_xwindow_id(GST_X_OVERLAY(videoOut), id);
}

int main(int argc, char *argv[])
{
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()){
        std::cerr <<"yarpserver not running - run yarpserver"<< std::endl;
        exit(EXIT_FAILURE);
    }
    // yarp network initialization
    yarp.init();
    
    gst_init(&argc, &argv);
    QApplication a(argc, argv);

    MainWindow window(&yarp);
    for(int i=0;i<8;i++) addVideo(window.getPort(i),window.getWinId(i));

    window.show();
    return a.exec();
}