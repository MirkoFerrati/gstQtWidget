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

    QVBoxLayout* combo_layout_0 = new QVBoxLayout();
    QLabel* combo_label_0 = new QLabel("Port:");
    combo_layout_0->addWidget(combo_label_0);
    video_0_combobox = new QComboBox();
    video_0_combobox->addItem(QString("1234"));
    video_0_combobox->addItem(QString("1235"));
    video_0_combobox->addItem(QString("1236"));
    combo_layout_0->addWidget(video_0_combobox);
    video_0_layout->addLayout(combo_layout_0);

    video_0_spinbox = new QSpinBox();
    video_0_spinbox->setValue(15);
    QLabel* spin_label_0 = new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_0 = new QHBoxLayout();
    spin_layout_0->addWidget(video_0_spinbox);
    spin_layout_0->addWidget(spin_label_0);
    video_0_layout->addLayout(spin_layout_0);

    video_0_enable = new QPushButton();
    video_0_enable->setCheckable(true);
    video_0_enable->setText("Enable");
    video_0_layout->addWidget(video_0_enable);



    video_1_layout = new QVBoxLayout();
    video_1_label = new QLabel(QString("Video 1"));
    video_1_layout->addWidget(video_1_label);

    QVBoxLayout* combo_layout_1 = new QVBoxLayout();
    QLabel* combo_label_1 = new QLabel("Port:");
    combo_layout_1->addWidget(combo_label_1);
    video_1_combobox = new QComboBox();
    video_1_combobox->addItem(QString("1234"));
    video_1_combobox->addItem(QString("1235"));
    video_1_combobox->addItem(QString("1236"));
    video_1_combobox->setCurrentIndex(1);
    combo_layout_1->addWidget(video_1_combobox);
    video_1_layout->addLayout(combo_layout_1);

    video_1_spinbox = new QSpinBox();
    video_1_spinbox->setValue(15);
    QLabel* spin_label_1= new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_1 = new QHBoxLayout();
    spin_layout_1->addWidget(video_1_spinbox);
    spin_layout_1->addWidget(spin_label_1);
    video_1_layout->addLayout(spin_layout_1);

    video_1_enable = new QPushButton();
    video_1_enable->setText("Enable");
    video_1_enable->setCheckable(true);
    video_1_layout->addWidget(video_1_enable);



    video_2_layout = new QVBoxLayout();
    video_2_label = new QLabel(QString("Video 2"));
    video_2_layout->addWidget(video_2_label);

    QVBoxLayout* combo_layout_2 = new QVBoxLayout();
    QLabel* combo_label_2 = new QLabel("Port:");
    combo_layout_2->addWidget(combo_label_2);
    video_2_combobox = new QComboBox();
    video_2_combobox->addItem(QString("1234"));
    video_2_combobox->addItem(QString("1235"));
    video_2_combobox->addItem(QString("1236"));
    video_2_combobox->setCurrentIndex(2);
    combo_layout_2->addWidget(video_2_combobox);
    video_2_layout->addLayout(combo_layout_2);

    video_2_spinbox = new QSpinBox();
    video_2_spinbox->setValue(15);
    QLabel* spin_label_2 = new QLabel(QString("  fps"));
    QHBoxLayout* spin_layout_2 = new QHBoxLayout();
    spin_layout_2->addWidget(video_2_spinbox);
    spin_layout_2->addWidget(spin_label_2);
    video_2_layout->addLayout(spin_layout_2);

    video_2_enable = new QPushButton();
    video_2_enable->setText("Enable");
    video_2_enable->setCheckable(true);
    video_2_layout->addWidget(video_2_enable);



    ui->controls_layout->addLayout(video_0_layout);
    ui->controls_layout->addLayout(video_1_layout);
    ui->controls_layout->addLayout(video_2_layout);

    connect(video_0_enable,SIGNAL(clicked()),this,SLOT(on_video_0_enable_clicked()));
    connect(video_1_enable,SIGNAL(clicked()),this,SLOT(on_video_1_enable_clicked()));
    connect(video_2_enable,SIGNAL(clicked()),this,SLOT(on_video_2_enable_clicked()));

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

void MainWindow::on_video_0_enable_clicked()
{
    if(video_0_enable->isChecked())
    {
        video_0_enable->setText("Disable");
    }
    else
    {
        video_0_enable->setText("Enable");
    }
}

void MainWindow::on_video_1_enable_clicked()
{
    if(video_1_enable->isChecked())
    {
        video_1_enable->setText("Disable");
    }
    else
    {
        video_1_enable->setText("Enable");
    }
}

void MainWindow::on_video_2_enable_clicked()
{
    if(video_2_enable->isChecked())
    {
        video_2_enable->setText("Disable");
    }
    else
    {
        video_2_enable->setText("Enable");
    }
}

