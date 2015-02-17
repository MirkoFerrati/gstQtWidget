#include "gstqtMedia.h"
#include "gstqtwidget.h"

#include <QBoxLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QMouseEvent>

gstqtMedia::gstqtMedia(QWidget *parent)
   : QWidget(parent)
{
   //create the player
  video_display[1234]=new gstqtwidget(this);
  video_display[1235]=new gstqtwidget(this);
   video_display[1234]->setPipeline(1234);
   video_display[1235]->setPipeline(1235);

   //create the UI
   QVBoxLayout *appLayout = new QVBoxLayout;
   appLayout->setContentsMargins(0, 0, 0, 0);
   createUI(appLayout);
   setLayout(appLayout);

   onStateChanged(); //set the controls to their default state

   setWindowTitle(tr("QtGStreamer example player"));
   resize(400, 400);
}

gstqtMedia::~gstqtMedia()
{

}

void gstqtMedia::onStateChanged()
{
}



void gstqtMedia::createUI(QBoxLayout *appLayout)
{
    QHBoxLayout* control_layout = new QHBoxLayout();
        QVBoxLayout* video_layout = new QVBoxLayout();
  video_layout->addWidget(  video_display[1234]);
  video_layout->addWidget(video_display[1235]);
  int glob_id=1234;

  QLabel* video_label = new QLabel("cam. "+QString::fromStdString(std::to_string(glob_id))+" [fps 1-30]:");
	video_switch[glob_id] = new QPushButton("Running");
	video_switch.at(glob_id)->setCheckable(true);
	video_switch.at(glob_id)->setChecked(true);
	video_saving[glob_id] = new QPushButton("Saving");
	video_saving.at(glob_id)->setCheckable(true);
	video_saving.at(glob_id)->setChecked(true);
	video_timer_edit[glob_id] = new QLineEdit();
	video_timer_edit[glob_id]->setEnabled(false);
	video_timer_edit.at(glob_id)->setFixedSize(60,30);
	video_timer_edit.at(glob_id)->setText(QString::number(1));
	  control_layout->addWidget(video_switch.at(glob_id));
  control_layout->addWidget(video_saving.at(glob_id));
  control_layout->addWidget(video_label);
  control_layout->addWidget(video_timer_edit.at(glob_id));
  video_layout->addLayout(control_layout);
  	appLayout->addLayout(video_layout);

}