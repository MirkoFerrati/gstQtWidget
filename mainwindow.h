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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    WId getWinId(int index=0);

private Q_SLOTS:
    void on_video_switch_clicked(const int& id);
    void on_video_saving_clicked(const int& id);
    void on_video_timer_changed(const int& id);
    void timers_body(const int& id);
    void on_save_menu_clicked();

private:
    QGridLayout main_layout;

    std::map<int,QPushButton*> video_switch;
    std::map<int,QPushButton*> video_saving;
    std::map<int,QLineEdit*> video_timer_edit;
    std::map<int,QWidget*> video_display;
    std::map<int,QTimer*> video_timer;
    
    QMenuBar menu_bar;
    QMenu* file_menu;
    QAction save_action;
    int glob_id=0;
};

#endif // MAINWINDOW_H
