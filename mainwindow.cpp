#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>  // Video write
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <unistd.h>
#include <QPixmap>

using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //vc = new VideoCapture("/home/opsroom/Data/SharedVideos/TrackingVideo.mp4");
    vc = new VideoCapture("/home/opsroom/Data/SharedVideos/TrackingVideo.mp4");
    vrw = new VideoReadWrite(vc,frame,false,"/home/opsroom/Data/SharedVideos/TrackingVideo111111111.mp4");
    azi = 0;
    elev = 0;
    state = 0;
    checked = false;
    recording = false;
    //    connect(this,SIGNAL(setTurretData(float,float,QPixmap,bool)),vrw,
    //                 SLOT(video_capture_handler(float,float,QPixmap,bool)));

    connect(this,SIGNAL(setTurretImg(QImage)),vrw,
            SLOT(getTurretImg(QImage)));

}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::on_pushButton_clicked()
{


    if(checked == false)
    {
        checked = true;

        t_cap = std::thread(&MainWindow::videoGetSet,this);
        ui->pushButton->setText("Stop Receive");
    }
    else
    {
        checked = false;
        ui->pushButton->setText("Start Receive");
    }

}

void MainWindow::on_checkBox_toggled(bool checked)
{
    recording = checked;

}

void MainWindow::videoGetSet()
{
    while(checked == true) //Show the image captured in the window and repeat
    {
        *vc >> this->frame;

        if (this->frame.empty())
            break;
        else
        {
            //            emit setTurretData(azi,elev, QPixmap::fromImage(QImage(frame.data, \
            //                                                                    frame.cols, \
            //                                                                    frame.rows, \
            //                                                                    frame.step, \
            //                                                                    QImage::Format_RGB888).rgbSwapped()), recording);

            emit setTurretImg(QImage(frame.data, \
                                     frame.cols, \
                                     frame.rows, \
                                     frame.step, \
                                     QImage::Format_RGB888).rgbSwapped());
            cout << "frame received" << endl;
        }

        usleep(40000);

    }
}
float MainWindow::stateAngle(float min, float max, float* Angle, unsigned char *State ,float deltaAngle)
{
    //function to simulate angle values
    float *angle = Angle;
    unsigned char *state = State;


    if(*state < 0x80) //increasing
    {
        switch (*state)
        {
        case 0x00: // 0 to max
            *angle = *angle + deltaAngle;
            if(*angle >= max)
                *state = 0x81;
            break;
        }
    }
    else if(*state > 0x80)//decreasing
    {
        switch (*state)
        {
        case 0x81: // max to 0
            *angle = *angle  - deltaAngle;
            if(*angle < min)
                *state  = 0x00;
            break;
        }
    }


    return *angle;
}

