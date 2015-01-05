#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void onMouse( int event, int x, int y, int, void* );
using namespace cv;

using namespace std;

//Mat img = cv::imread("b.jpg", 0); // force grayscale
//Mat thresh=Mat::zeros(img.size(),CV_8UC1);
Mat binary;
Mat img;
int main(int argc, char **argv)
{

VideoCapture cap(0); //capture the video from web cam
    //image object

if ( !cap.isOpened() )  // if not success, exit program
{
  cout << "Cannot open the web cam" << endl;
  return -1;
}



while(true)
{
  //img = imread("../test_img.png");
bool bSuccess = cap.read(img); // read a new frame from video

//  threshold(img,gray,50,255,THRESH_TOZERO);

  namedWindow("thresh");
  setMouseCallback( "thresh", onMouse, 0 );

  imshow("thresh",img);

  if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
  {
    cout << "esc key is pressed by user" << endl;
    break;
  }
}}

void onMouse( int event, int x, int y, int, void* )
{
  if( event != CV_EVENT_LBUTTONDOWN )
    return;

    Point pt = Point(x,y);
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valueblue="<< (int)img.at<Vec3b>(y,x)[0]<<"\n";
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valuegreen="<< (int)img.at<Vec3b>(y,x)[1]<<"\n";
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y<<"\t valuered="<< (int)img.at<Vec3b>(y,x)[2]<<"\n";

  }
