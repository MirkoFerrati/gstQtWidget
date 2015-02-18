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
  for (int i=1230;i<1236;i++)
  {
    video_display[i]=new gstqtwidget(this);
    video_display[i]->setPipeline(i);
  }
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
    QHBoxLayout* mainvideo = new QHBoxLayout();
  
    QHBoxLayout* control_layout = new QHBoxLayout();
        QVBoxLayout* video_layout = new QVBoxLayout();
	QVBoxLayout* video_layout1 = new QVBoxLayout();
	
	   //create the player
  for (int i=1230;i<1233;i++)
  {
    video_layout->addWidget(  video_display[i]);
  }
  for (int i=1233;i<1236;i++)
  {
    video_layout1->addWidget(  video_display[i]);
  }

  int glob_id=1230;

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
  mainvideo->addLayout(video_layout);
    mainvideo->addLayout(video_layout1);
  	appLayout->addLayout(mainvideo);
	  appLayout->addLayout(control_layout);


}