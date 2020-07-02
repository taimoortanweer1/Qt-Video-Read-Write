#ifndef VIDEOREADWRITE_H
#define VIDEOREADWRITE_H

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <thread>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>  // Video write
#include <opencv2/opencv.hpp>

#include <QObject>

using namespace cv;
using namespace std;

namespace Ui {
class VideoReadWrite;
}

class VideoReadWrite : public QObject
{

Q_OBJECT

public:
    VideoReadWrite(VideoCapture *inputVideo ,Mat inputFrame, bool start, cv::String deststr);
    ~VideoReadWrite();

    Point getTurretPosition();
    void setTurretPosition(Point pos);
    void setStartSync(bool start);
    void setTurretImg(Mat img);

    VideoCapture *inputVideo;
    VideoWriter  *vwrite;
    cv::String destString;
    Size sizeOfVideo;
    int codec;
    bool endFlag;
    //std::thread t_cap;
    Mat Frame;
    bool start;

public slots:
    //void  video_capture_handler(float azi, float elev, QPixmap img, bool enable);
    //void getTurretData(Point pos, Mat img);
    void getTurretImg(QImage img);

public:


};

#endif // VIDEOREADWRITE_H
