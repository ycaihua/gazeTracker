
//Author Amit & Manasi
#include <iostream>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

// structure for centroids
typedef struct center
{
  int x=0;
  int y=0;
};

/*function Headers*/


/*Global variables*/
Mat img;   //image object

int blueL = 0;
int blueH = 25;

int greenL = 0;
int greenH = 15;

int redL = 0;
int redH = 15;

int flag=0;

void onMouse( int event, int x, int y, int, void* )
{
  if( event != CV_EVENT_LBUTTONDOWN )
    return;

    Point pt = Point(x,y);
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valueblue="<< (int)img.at<Vec3b>(y,x)[0]<<"\n";
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valuegreen="<< (int)img.at<Vec3b>(y,x)[1]<<"\n";
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valuered="<< (int)img.at<Vec3b>(y,x)[2]<<"\n";

    return ;

  }


void pupilDetect(Mat roi)
{
  Mat imgThresholded;
  //Thresholding the image
  inRange(roi, Scalar(blueL, greenL, redL), Scalar(blueH, greenH, redH), imgThresholded);


  imshow("thresholded",imgThresholded);

}

int main(int argc,char *argv)
{

  VideoCapture cap(1); //capture the video from web cam
       //image object

  if ( !cap.isOpened() )  // if not success, exit program
  {
    cout << "Cannot open the web cam" << endl;
    return -1;
  }

  namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  //Create trackbars in "Control" window
  cvCreateTrackbar("blueL", "Control", &blueL, 179); //Hue (0 - 179)
  cvCreateTrackbar("blueH", "Control", &blueH, 179);

  cvCreateTrackbar("greenL", "Control", &greenL, 255); //Saturation (0 - 255)
  cvCreateTrackbar("greenH", "Control", &greenH, 255);

  cvCreateTrackbar("redL", "Control", &redL, 255); //Value (0 - 255)
  cvCreateTrackbar("redH", "Control", &redH, 255);
  cvCreateTrackbar("finalize", "Control", &flag, 1);




while(true)
{
  bool bSuccess = cap.read(img); // read a new frame from video
  rectangle(img,Point(268,409),Point(513,106),Scalar(255,0,0),5,8);
  Mat roi = img(Rect(268,111,300,250));

  namedWindow("original");
  setMouseCallback( "original", onMouse, 0 );
  imshow("original",img);
  imshow("roi",roi);
  if (!bSuccess) //if not success, break loop
  {
    cout << "Cannot read a frame from video stream" << endl;
    break;
  }

  if (flag==0)
  {
    pupilDetect(roi);

  }
  else if(flag==1)
  {
      break;
  }

  if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
  {
    cout << "esc key is pressed by user" << endl;
    break;
  }

}

cap.release();
return 0;

}
