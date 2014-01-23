#ifndef STREAMING_WINDOW_H
#define STREAMING_WINDOW_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include "GstSupport/GstSupport.h"
#include "GstSupport/GstWidget.h"
#include <boost/scoped_ptr.hpp>

class streaming_window:public QWidget
{
Q_OBJECT
public:
    streaming_window(QWidget *parent = 0);
    ~streaming_window();

private Q_SLOTS:

private:
  QGridLayout* main_layout;

//  QVBoxLayout* vertical_layout_1;
//  QVBoxLayout* vertical_layout_2;

  GstElement* bin;
  Gst::Widget* mGstWidget;
  const char * cPipeline;
public:

};

#endif // STREAMING_WINDOW_H
