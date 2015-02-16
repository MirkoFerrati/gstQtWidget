#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), save_action(tr("&Save"),parent)
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(&save_action);

    connect(&save_action,SIGNAL(triggered()),this,SLOT(on_save_menu_clicked()));

    QSignalMapper* switch_signalMapper = new QSignalMapper(this);
    QSignalMapper* saving_signalMapper = new QSignalMapper(this);
    QSignalMapper* timeredit_signalMapper = new QSignalMapper(this);
    QSignalMapper* timer_signalMapper = new QSignalMapper(this);

    int i=0;
    int j=0;

    while(glob_id<8)
    {
        if(j>3)
	{
	    i++;
	    j=0;
	}
        QVBoxLayout* video_layout = new QVBoxLayout();
	QHBoxLayout* control_layout = new QHBoxLayout();
	QLabel* video_label = new QLabel("cam. "+QString::fromStdString(std::to_string(glob_id))+" [s]:");
	video_label->setFixedSize(60,30);

	video_switch[glob_id] = new QPushButton("Running");
	video_switch.at(glob_id)->setCheckable(true);
	video_switch.at(glob_id)->setChecked(true);
	video_saving[glob_id] = new QPushButton("Saving");
	video_saving.at(glob_id)->setCheckable(true);
	video_saving.at(glob_id)->setChecked(true);
	video_timer_edit[glob_id] = new QLineEdit();
	video_timer_edit.at(glob_id)->setFixedSize(60,30);
	video_timer_edit.at(glob_id)->setText(QString::number(1.0, 'f', 2));
	video_display[glob_id] = new QWidget();
	video_timer[glob_id] = new QTimer();
	video_timer.at(glob_id)->start(video_timer_edit.at(glob_id)->text().toDouble()*1000.0);

	video_layout->addWidget(video_display.at(glob_id));
	control_layout->addWidget(video_switch.at(glob_id));
	control_layout->addWidget(video_saving.at(glob_id));
	control_layout->addWidget(video_label);
	control_layout->addWidget(video_timer_edit.at(glob_id));
	video_layout->addLayout(control_layout);
	main_layout.addLayout(video_layout,i,j++,Qt::AlignCenter);

	connect(video_switch.at(glob_id), SIGNAL(clicked(bool)), switch_signalMapper, SLOT(map()));
	switch_signalMapper->setMapping(video_switch.at(glob_id), glob_id);
	connect(video_saving.at(glob_id), SIGNAL(clicked(bool)), saving_signalMapper, SLOT(map()));
	saving_signalMapper->setMapping(video_saving.at(glob_id), glob_id);
	connect(video_timer_edit.at(glob_id), SIGNAL(returnPressed()), timeredit_signalMapper, SLOT(map()));
	timeredit_signalMapper->setMapping(video_timer_edit.at(glob_id), glob_id);
	connect(video_timer.at(glob_id), SIGNAL(timeout()), timer_signalMapper, SLOT(map()));
	timer_signalMapper->setMapping(video_timer.at(glob_id), glob_id);
	glob_id++;
    }

    connect(switch_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_switch_clicked(int)));
    connect(saving_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_saving_clicked(int)));
    connect(timeredit_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_video_timer_changed(int)));
    connect(timer_signalMapper, SIGNAL(mapped(int)), this, SLOT(timers_body(int)));
    
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(&main_layout);
}

WId MainWindow::getWinId(int index)
{
    return video_display.at(index)->winId();
}

void MainWindow::on_video_saving_clicked(const int& id)
{
    if(video_saving.at(id)->isChecked())
    {
	video_saving.at(id)->setText("Saving");
    }
    else
    {
        video_saving.at(id)->setText("Not Saving");
    }

    std::cout<<"save: To be implemented"<<std::endl;
}

void MainWindow::on_video_switch_clicked(const int& id)
{
    if(video_switch.at(id)->isChecked())
    {
	video_switch.at(id)->setText("Running");
    }
    else
    {
        video_switch.at(id)->setText("Stopped");
    }

    std::cout<<"switch: To be implemented "<<std::endl;
}

void MainWindow::on_video_timer_changed(const int& id)
{
    video_timer.at(id)->setInterval(video_timer_edit.at(id)->text().toDouble()*1000.0);
}

void MainWindow::timers_body(const int& id)
{
    std::cout<<"timer body: To be implemented "<<id<<std::endl;
}

void MainWindow::on_save_menu_clicked()
{
    std::cout<<"save menu: To be implemented"<<std::endl;
}

MainWindow::~MainWindow()
{

}