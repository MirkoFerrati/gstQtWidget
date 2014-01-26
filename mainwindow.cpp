#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    video_0_layout = new QVBoxLayout();
    video_0_label = new QLabel(QString("Video 0"));
    video_0_layout->addWidget(video_0_label);

    video_0_combobox = new QComboBox();
    video_0_combobox->addItem(QString("/dev/video0"));
    video_0_combobox->addItem(QString("/dev/video1"));
    video_0_combobox->addItem(QString("/dev/video2"));
    video_0_layout->addWidget(video_0_combobox);

    video_0_spinbox = new QSpinBox();
    video_0_spinbox->setValue(15);
    QLabel* spin_label_0 = new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_0 = new QHBoxLayout();
    spin_layout_0->addWidget(video_0_spinbox);
    spin_layout_0->addWidget(spin_label_0);
    video_0_layout->addLayout(spin_layout_0);

    video_0_enable = new QPushButton();
    video_0_enable->setText("Enable");
    video_0_layout->addWidget(video_0_enable);



    video_1_layout = new QVBoxLayout();
    video_1_label = new QLabel(QString("Video 1"));
    video_1_layout->addWidget(video_1_label);

    video_1_combobox = new QComboBox();
    video_1_combobox->addItem(QString("/dev/video0"));
    video_1_combobox->addItem(QString("/dev/video1"));
    video_1_combobox->addItem(QString("/dev/video2"));
    video_1_combobox->setCurrentIndex(1);
    video_1_layout->addWidget(video_1_combobox);

    video_1_spinbox = new QSpinBox();
    video_1_spinbox->setValue(15);
    QLabel* spin_label_1= new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_1 = new QHBoxLayout();
    spin_layout_1->addWidget(video_1_spinbox);
    spin_layout_1->addWidget(spin_label_1);
    video_1_layout->addLayout(spin_layout_1);

    video_1_enable = new QPushButton();
    video_1_enable->setText("Enable");
    video_1_layout->addWidget(video_1_enable);



    video_2_layout = new QVBoxLayout();
    video_2_label = new QLabel(QString("Video 2"));
    video_2_layout->addWidget(video_2_label);

    video_2_combobox = new QComboBox();
    video_2_combobox->addItem(QString("/dev/video0"));
    video_2_combobox->addItem(QString("/dev/video1"));
    video_2_combobox->addItem(QString("/dev/video2"));
    video_2_combobox->setCurrentIndex(2);
    video_2_layout->addWidget(video_2_combobox);

    video_2_spinbox = new QSpinBox();
    video_2_spinbox->setValue(15);
    QLabel* spin_label_2 = new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_2 = new QHBoxLayout();
    spin_layout_2->addWidget(video_2_spinbox);
    spin_layout_2->addWidget(spin_label_2);
    video_2_layout->addLayout(spin_layout_2);

    video_2_enable = new QPushButton();
    video_2_enable->setText("Enable");
    video_2_layout->addWidget(video_2_enable);



    ui->controls_layout->addLayout(video_0_layout);
    ui->controls_layout->addLayout(video_1_layout);
    ui->controls_layout->addLayout(video_2_layout);
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
