#ifndef gstqtMedia_H
#define gstqtMedia_H

#include <QTimer>
#include <QWidget>
#include <QStyle>
#include <QLineEdit>
#include <QPushButton>
#include <map>

class gstqtwidget;
class QBoxLayout;
class QLabel;
class QSlider;
class QToolButton;
class QTimer;

class gstqtMedia : public QWidget
{
   Q_OBJECT
public:
   gstqtMedia(QWidget *parent = 0);
   ~gstqtMedia();


private Q_SLOTS:
   void onStateChanged();

protected:

private:
   void createUI(QBoxLayout *appLayout);

    std::map<int,QPushButton*> video_switch;
    std::map<int,QPushButton*> video_saving;
    std::map<int,QLineEdit*> video_timer_edit;
    std::map<int,gstqtwidget*> video_display;
    std::map<int,int> video_fps;
    std::map<int,std::string> command_map;
    std::map<int,int> video_port;
//     std::map<int,yarp::os::Port*> command_port;
// //    gstqtwidget *m_player;
//    gstqtwidget *m_player1;
   QTimer m_fullScreenTimer;
};

#endif