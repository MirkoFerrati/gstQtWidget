#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    WId getWinId(int index=0);

private Q_SLOTS:
    void on_video_0_enable_clicked();
    void on_video_1_enable_clicked();
    void on_video_2_enable_clicked();


private:
    Ui::MainWindow *ui;

    QVBoxLayout* video_0_layout;
    QVBoxLayout* video_1_layout;
    QVBoxLayout* video_2_layout;

    QLabel* video_0_label;
    QLabel* video_1_label;
    QLabel* video_2_label;

    QPushButton* video_0_enable;
    QPushButton* video_1_enable;
    QPushButton* video_2_enable;

    QComboBox* video_0_combobox;
    QComboBox* video_1_combobox;
    QComboBox* video_2_combobox;

    QSpinBox* video_0_spinbox;
    QSpinBox* video_1_spinbox;
    QSpinBox* video_2_spinbox;
};

#endif // MAINWINDOW_H
