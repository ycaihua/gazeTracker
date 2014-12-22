#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;
Mat image,median_image;
int blur_filter_value = 5;

void medianFiltering(int,void*)
{
  medianBlur(image,median_image,2*(blur_filter_value)+1);
  imshow("median_filter",median_image);
}

int main(int argc,char** argv)
{
  image= imread(argv[1]);
  namedWindow("median_filter",CV_WINDOW_AUTOSIZE);
  createTrackbar("Blurring","median_filter",&blur_filter_value,10,medianFiltering);
  medianFiltering(0,0);
  while (true)
  {
    int c;
    c=waitKey(20);
    if((char)c==27)
    {break;}
  }
}
