#include "gstqtMedia.h"
#include "gstqtwidget.h"

#include <QBoxLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QMouseEvent>
#include <QSignalMapper>

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
    QVBoxLayout* video_layout0 = new QVBoxLayout();
    QVBoxLayout* video_layout1 = new QVBoxLayout();
    QVBoxLayout* video_layout2 = new QVBoxLayout();
 
    QSignalMapper* switch_signalMapper = new QSignalMapper(this);
    QSignalMapper* saving_signalMapper = new QSignalMapper(this);
    QSignalMapper* timeredit_signalMapper = new QSignalMapper(this);
    
    int j=0;
    int port=1230;
    int glob_id=0;
    
    while(glob_id<9)
    {
        QVBoxLayout* video_layout = new QVBoxLayout();
        QHBoxLayout* control_layout = new QHBoxLayout();
        QLabel* video_label = new QLabel("cam. "+QString::fromStdString(std::to_string(glob_id))+" [fps 1-30]:");
        
        video_port[glob_id] = port;
        
        video_switch[glob_id] = new QPushButton("Stopped");
        video_switch.at(glob_id)->setCheckable(true);
        video_switch.at(glob_id)->setChecked(false);
        video_saving[glob_id] = new QPushButton("Saving");
        video_saving.at(glob_id)->setCheckable(true);
        video_saving.at(glob_id)->setChecked(true);
        video_timer_edit[glob_id] = new QLineEdit();
        video_timer_edit[glob_id]->setEnabled(false);
        video_timer_edit.at(glob_id)->setFixedSize(60,30);
        video_timer_edit.at(glob_id)->setText(QString::number(1));
        video_display[glob_id] = new gstqtwidget(this);
        video_display.at(glob_id)->setPipeline(video_port[glob_id]);
        video_fps[glob_id] = video_timer_edit.at(glob_id)->text().toInt();
        
        video_layout->addWidget(video_display.at(glob_id));
        control_layout->addWidget(video_switch.at(glob_id));
        control_layout->addWidget(video_saving.at(glob_id));
        control_layout->addWidget(video_label);
        control_layout->addWidget(video_timer_edit.at(glob_id));
        video_layout->addLayout(control_layout);
        
        if(j<3)video_layout0->addLayout(video_layout);
        else if(j<6) video_layout1->addLayout(video_layout);
        else  video_layout2->addLayout(video_layout);
        j++;
        
        command_map[glob_id] = "./camera_rec video"+std::to_string(glob_id)+" "+std::to_string(video_port.at(glob_id))+" &";
        //      system(command_map.at(glob_id).c_str());
        command_port[glob_id] = new yarp::os::Port();
        command_port.at(glob_id)->open("/camera_gui/video"+std::to_string(glob_id));

	yarp::os::ContactStyle style;
	style.persistent = true;
        yarp::os::Network::connect("/camera_rec/video"+std::to_string(glob_id),"/camera_gui/video"+std::to_string(glob_id), style);
        
        connect(video_switch.at(glob_id), SIGNAL(clicked(bool)), switch_signalMapper, SLOT(map()));
        switch_signalMapper->setMapping(video_switch.at(glob_id), glob_id);
        connect(video_saving.at(glob_id), SIGNAL(clicked(bool)), saving_signalMapper, SLOT(map()));
        saving_signalMapper->setMapping(video_saving.at(glob_id), glob_id);
        connect(video_timer_edit.at(glob_id), SIGNAL(returnPressed()), timeredit_signalMapper, SLOT(map()));
        timeredit_signalMapper->setMapping(video_timer_edit.at(glob_id), glob_id);
        glob_id++;
        port++;
    }
    
    mainvideo->addLayout(video_layout0);
    mainvideo->addLayout(video_layout1);
    mainvideo->addLayout(video_layout2);
    appLayout->addLayout(mainvideo);
    
    QPushButton* save_button = new QPushButton("Save");
    QPushButton* quit_all_button = new QPushButton("Quit All");
    QHBoxLayout* but_layout = new QHBoxLayout();
    but_layout->addWidget(save_button);
    but_layout->addWidget(quit_all_button);
    
    appLayout->addLayout(but_layout);
    
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(on_save_menu_clicked()));
    connect(quit_all_button, SIGNAL(clicked(bool)), this, SLOT(on_quit_all_button_clicked()));
    connect(switch_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_switch_clicked(int)));
    connect(saving_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_saving_clicked(int)));
    connect(timeredit_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_fps_changed(int)));
}


void gstqtMedia::on_video_saving_clicked(const int& id)
{
    if(video_saving.at(id)->isChecked())
    {
        video_saving.at(id)->setText("Saving");
        yarp::os::Bottle command;
        command.addString("saving");
        command_port.at(id)->write(command);
    }
    else
    {
        video_saving.at(id)->setText("Not Saving");
        yarp::os::Bottle command;
        command.addString("nosaving");
        command_port.at(id)->write(command);
    }
}

void gstqtMedia::on_video_switch_clicked(const int& id)
{
    if(video_switch.at(id)->isChecked())
    {
        video_switch.at(id)->setText("Running");
        system(command_map.at(id).c_str());
    }
    else
    {
        video_switch.at(id)->setText("Stopped");
        yarp::os::Bottle command;
        command.addString("quit");
        command_port.at(id)->write(command);
    }
}

void gstqtMedia::on_video_fps_changed(const int& id)
{
    video_fps.at(id) = video_timer_edit.at(id)->text().toInt();\
    if(video_fps.at(id)>30) video_fps.at(id)=30;
    if(video_fps.at(id)<1) video_fps.at(id)=1;
    video_timer_edit.at(id)->setText(QString::number(video_fps.at(id)));
    yarp::os::Bottle command;
    command.addString("period "+ std::to_string(video_fps.at(id)));
    command_port.at(id)->write(command);
}

void gstqtMedia::on_save_menu_clicked()
{
    yarp::os::Bottle command;
    command.addString("save");
    for(auto item:command_port) item.second->write(command);
}

void gstqtMedia::on_quit_all_button_clicked()
{
    yarp::os::Bottle command;
    command.addString("quit");
    for(auto item:command_port) item.second->write(command);
}