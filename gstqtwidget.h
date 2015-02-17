
#ifndef gstqtwidget_H
#define gstqtwidget_H

#include <QTimer>
#include <QTime>
#include <QGst/Pipeline>
#include <QGst/Ui/VideoWidget>
#include <QGst/Utils/ApplicationSink>
#include <QGst/Utils/ApplicationSource>


class gstqtwidget : public QGst::Ui::VideoWidget
{
    Q_OBJECT
public:
    gstqtwidget(QWidget *parent = 0);
    ~gstqtwidget();

    void setPipeline(int port);

private:
    
    QGst::PipelinePtr m_pipeline;
};

#endif
