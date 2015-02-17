#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QTimer>
#include <QMenuBar>
#include <QMenu>
#include <QSignalMapper>
#include <iostream>
#include <yarp/os/all.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(yarp::os::Network* yarp, QWidget *parent = 0);
    ~MainWindow();

    WId getWinId(int index);
    int getPort(int index);

private Q_SLOTS:
    void on_video_switch_clicked(const int& id);
    void on_video_saving_clicked(const int& id);
    void on_video_fps_changed(const int& id);
    void on_save_menu_clicked();

private:
    QGridLayout main_layout;

    std::map<int,QPushButton*> video_switch;
    std::map<int,QPushButton*> video_saving;
    std::map<int,QLineEdit*> video_timer_edit;
    std::map<int,QWidget*> video_display;
    std::map<int,int> video_fps;
    std::map<int,std::string> command_map;
    std::map<int,int> video_port;
    std::map<int,yarp::os::Port*> command_port;
    
    QMenuBar menu_bar;
    QMenu* file_menu;
    QAction save_action;
    int glob_id=0;
};

#endif // MAINWINDOW_H
