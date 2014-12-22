

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;
Mat image,smoothened_image;
int blur_filter_value = 5;
int selection_value=0;
int gaussian_filter_value=5;
int i=1;

void medianFiltering(int,void*)
{
  medianBlur(image,smoothened_image,2*(blur_filter_value)+3);
  imshow("output_image",smoothened_image);
}

void gaussian_filter(int,void*)
{
  GaussianBlur( image,smoothened_image ,Size(2*i+1,2*i+1), 0, 0 );
  imshow("output_image",smoothened_image);
}

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



int main(int argc,char** argv)
{
  image= imread(argv[1]);
  namedWindow("output_image",CV_WINDOW_AUTOSIZE);
  createTrackbar("Selection","output_image",&selection_value,2,Selection);
  createTrackbar("Median_filtering","output_image",&blur_filter_value,10,medianFiltering);
  createTrackbar("Gaussian_filtering","output_image",&i,10,gaussian_filter);
  //medianFiltering(0,0);
  while (true)
  {
    int c;
    c=waitKey(20);
    if((char)c==27)
    {break;}
  }
}
