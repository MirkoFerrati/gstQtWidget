
#include "gstqtwidget.h"
#include <QDir>
#include <QUrl>
#include <qmessagebox.h>
#include <gstreamer-0.10/gst/gstparse.h>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Bus>
#include <QGst/Message>
#include <QGst/Query>
#include <QGst/ClockTime>
#include <QGst/Parse>
#include <QGst/Event>
#include <QGst/StreamVolume>
#include <assert.h>

gstqtwidget::gstqtwidget(QWidget *parent)
    : QGst::Ui::VideoWidget(parent)
{
}

gstqtwidget::~gstqtwidget()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
    }
}

void gstqtwidget::setPipeline(int port)
{
    QGst::ElementPtr src = QGst::ElementFactory::make("udpsrc","src");
    assert(src);
    QGst::ElementPtr dec = QGst::ElementFactory::make("jpegdec","dec");
    assert(dec);
    QGst::ElementPtr color = QGst::ElementFactory::make("ffmpegcolorspace","color");
    assert(color);
    QGst::ElementPtr sink = QGst::ElementFactory::make("ximagesink","sink");
    assert(sink);
    if (!src ||!dec || !color || !sink) {
        QMessageBox::critical(this, tr("Error"), tr("One or more elements could not be created. "
        "Verify that you have all the necessary element plugins installed."));
        return;
    }
    src->setProperty("port",port);
    
    m_pipeline = QGst::Pipeline::create();
    m_pipeline->add(src, dec, color, sink);
    //link elements
    src->link(dec);
    dec->link(color);
    color->link(sink);
    setVideoSink(sink);
    //connect the bus
    m_pipeline->bus()->addSignalWatch();
    //go!
    m_pipeline->setState(QGst::StatePlaying);
 
}

