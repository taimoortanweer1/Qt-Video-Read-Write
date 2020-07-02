#include "Videoreadwrite.h"
#include <QPixmap>
VideoReadWrite::VideoReadWrite(VideoCapture *inputVideo ,Mat inputFrame, bool start, cv::String deststr)
{
    this->inputVideo = inputVideo;
    this->Frame = inputFrame;
    this->start = start;
    this->destString = deststr;
    this->endFlag = false;

    codec = static_cast<int>(inputVideo->get(CAP_PROP_FOURCC));     // Get Codec Type- Int form
    sizeOfVideo = Size((int) inputVideo->get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
                       (int) inputVideo->get(CAP_PROP_FRAME_HEIGHT));

    outputVideo.open(destString + ".avi", codec, inputVideo->get(CAP_PROP_FPS), sizeOfVideo, true);

    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << endl;     
    }

}

VideoReadWrite::~VideoReadWrite()
{
    outputVideo.release();
    delete this;
}
//void VideoReadWrite::video_capture_handler(float azi,float elev, QPixmap Img, bool enable)
//{

//    QPixmap img = Img;
//    Mat src = cv::Mat(img.height(),img.width(),QImage::Format_RGB888);


//    if(enable)
//    {

//        this->Frame = src;

//        if (src.empty())
//        {
//            cout << "Finished writing" << endl;
//        }
//        else
//        {
//            imshow("video",src);
//            waitKey(1);
//           outputVideo.write(src); //save or

//            cout << "imshow received" << endl;

//        }
//    }
//}

void VideoReadWrite::getTurretImg(QImage img)
{
    QImage d = img;
}
Point VideoReadWrite::getTurretPosition()
{
    //return turretPosition;
}
void  VideoReadWrite::setTurretPosition(Point pos)
{
    //this->turretPosition.x = pos.x;
    //this->turretPosition.y = pos.y;
}

void VideoReadWrite::setStartSync(bool start)
{
    this->start = start;
}

void VideoReadWrite::setTurretImg(Mat img)
{
    this->Frame = img;
}
