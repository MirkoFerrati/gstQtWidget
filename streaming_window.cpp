#include "streaming_window.h"
#include <QtGui/QFileDialog>
#include <gst/gst.h>

extern "C"
{
    #include <gst/interfaces/xoverlay.h>
}

streaming_window::streaming_window(QWidget *parent)
{
    //cPipeline = "filesrc location=\"{{path}}\" ! decodebin2 name=d" " d. ! queue ! ffmpegcolorspace ! osxvideosink" " d. ! queue ! audioconvert ! audioresample ! autoaudiosink";


    //cPipeline="udpsrc port=1236 ! \"application/x-rtp, payload=127\" ! rtph264depay ! ffdec_h264 ! xvimagesink sync=false";

    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "/", tr("Video Files (*.avi *.mkv *.ogm *.wmv)"));
    //QString desc = cPipeline;
    //desc.replace("{{path}}", fileName);
    //mPipeline.reset(Gst::Pipeline::Parse(desc.toAscii().data()));
    //mGstWidget.reset(new Gst::Widget(mPipeline, reinterpret_cast<void*>(winId())));
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

    GstElement *videoOut = gst_element_factory_make("xvimagesink", "video out");
    g_assert(videoOut);

    gst_bin_add_many(GST_BIN(bin), testSrc,depay,h264, videoOut, NULL);
    //gst_element_link_many(testSrc, videoOut, NULL);

    gst_element_link_many (testSrc, depay,h264,videoOut,NULL);

    gst_element_set_state(GST_ELEMENT(bin), GST_STATE_PLAYING);
    //Gst::Pipeline::SetState(mPipeline, GST_STATE_PLAYING);

    main_layout=new QGridLayout();

    QWidget* temp=new QWidget();
   //mGstWidget=new Gst::Widget(bin, reinterpret_cast<void*>(temp->winId()));

    main_layout->addWidget(temp,0,0);

    gst_x_overlay_set_xwindow_id(GST_X_OVERLAY(videoOut), temp->winId());
setLayout(main_layout);
}

streaming_window::~streaming_window()
{
    Gst::Pipeline::SetState(bin, GST_STATE_NULL);
}
