#include <QtGui/QApplication>
#include <gst/gst.h>
#include "streaming_window.h"

int main(int argc, char *argv[])
{

    //gst-launch udpsrc port=1236 ! "application/x-rtp, payload=127" ! rtph264depay ! ffdec_h264 ! xvimagesink sync=false

    //QCoreApplication a(argc, argv);

    gst_init(&argc, &argv);
        QApplication a(argc, argv);

       gst_init (NULL,NULL);

       GstElement *bin = gst_pipeline_new ("pipeline");
       g_assert(bin);

       GstElement *testSrc = gst_element_factory_make("udpsrc", "source");
       g_assert(testSrc);

       g_object_set (G_OBJECT (testSrc), "port", 1234, NULL);
       g_object_set (G_OBJECT (testSrc), "caps",
               gst_caps_new_simple ("application/x-rtp",
                            "payload", G_TYPE_INT, 127,
                            NULL), NULL);

       GstElement *depay = gst_element_factory_make("rtph264depay", "depay");
       g_assert(depay);
       GstElement *h264 = gst_element_factory_make("ffdec_h264", "h264");
       g_assert(h264);

       GstElement *videoOut = gst_element_factory_make("autovideosink", "video out");
       g_assert(videoOut);

       gst_bin_add_many(GST_BIN(bin), testSrc,depay,h264, videoOut, NULL);
       //gst_element_link_many(testSrc, videoOut, NULL);

       gst_element_link_many (testSrc, depay,h264,videoOut,NULL);

       gst_element_set_state(GST_ELEMENT(bin), GST_STATE_PLAYING);

        streaming_window window;
        window.show();
       return a.exec();
}
