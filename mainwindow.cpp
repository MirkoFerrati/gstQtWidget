#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


WId MainWindow::getWinId(int index)
{
    if (index==0)
        return ui->video0->winId();
    if (index==1)
        return ui->video1->winId();
    if (index==2)
        return ui->video2->winId();

}
