
//Author Amit & Manasi
#include <iostream>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

//Global variables
Mat imgOriginal;     //image object
Mat imgT;
Mat edge_thresh;
int flag=0;
int iLowH = 130;
int iHighH = 179;

int iLowS = 90;
int iHighS = 255;

int iLowV = 90;
int iHighV = 255;


int main(int argc, char** argv)
{
    VideoCapture cap(0); //capture the video from web cam


    if ( !cap.isOpened() )  // if not success, exit program
      {
      cout << "Cannot open the web cam" << endl;
      return -1;
      }
      while(true)    // skin detection
      {

      bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
        cout << "Cannot read a frame from video stream" << endl;
        break;
        }

      namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
      //Create trackbars in "Control" window
      cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
      cvCreateTrackbar("HighH", "Control", &iHighH, 179);

      cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
      cvCreateTrackbar("HighS", "Control", &iHighS, 255);

      cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
      cvCreateTrackbar("HighV", "Control", &iHighV, 255);
      cvCreateTrackbar("finalize", "Control", &flag, 1);
      if(flag==0)
      {
        cvtColor(imgOriginal, imgT, COLOR_BGR2YUV);
        inRange(imgT, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgT);
      //  Canny(imgOriginal,edge_thresh,iLowH,iHighH,3);
        imshow("Thresholded Image", imgT); //show the thresholded image
        erode(imgT, imgT, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgT, imgT, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //morphological closing (fill small holes in the foreground)
        dilate( imgT, imgT, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(imgT, imgT, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        cv::imshow("imgT",imgT);

      }
      else if (flag==1)
      {
        destroyWindow("Control");
        destroyWindow("Thresholded Image");
        destroyWindow("imgT");
        //cout<<"mcen.x= "<<mcen.x<<" mcen.y= "<<mcen.y<<endl;  //print the centrois of marker
        flag=0;
        break;
      }
      if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
      {
        cout << "esc key is pressed by user" << endl;
        break;
      }

    }
}
