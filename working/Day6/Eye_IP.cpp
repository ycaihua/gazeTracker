#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;
Mat image,median_image,gaussian_image;
int blur_filter_value = 5;]
int selection_value=0;
int gaussian_filter_value=5;

void Selection(int,void*)
{
  if (selection_value == 0)
  {
    medianFiltering(0,0);
  }
  else
  {
    gaussian_filter(0,0);
  }

}

void medianFiltering(int,void*)
{
  medianBlur(image,median_image,2*(blur_filter_value)+3);
  imshow("output_image",median_image);
}

void gaussian_filter(int,void*)
{
  GaussianBlur( image,gaussian_image ,2*(gaussian_filter_value)+3, 0, 0 );
  imshow("output_image",gaussian_image);
}

int main(int argc,char** argv)
{
  image= imread(argv[1]);
  namedWindow("output_image",CV_WINDOW_AUTOSIZE);
  createTrackbar("Selection","output_image",&selection_value,2,Selection);
  createTrackbar("Median_filtering","output_image",&blur_filter_value,10,medianFiltering);
  createTrackbar("Gaussian_filtering","output_image",&gaussian_filter_value,,gaussian_filter);
  //medianFiltering(0,0);
  while (true)
  {
    int c;
    c=waitKey(20);
    if((char)c==27)
    {break;}
  }
}
