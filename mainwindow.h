#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <thread>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>  // Video write
#include "Videoreadwrite.h"


using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void setTurretData(float azi, float elev, QPixmap img, bool enable);
    void setTurretImg(QImage img);

private slots:
    void on_pushButton_clicked();
    void on_checkBox_toggled(bool checked);
    float stateAngle(float min, float max, float* Angle, unsigned char *State ,float deltaAngle);
    void videoGetSet();

private:
    Ui::MainWindow *ui;
    VideoCapture *vc;
    VideoReadWrite *vrw;
    Mat frame;
    float azi;
    float elev;
    std::thread t_cap;
    unsigned char state;
    bool checked;
    bool recording;



};

#endif // MAINWINDOW_H
