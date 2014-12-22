/*
* Project Name: Adjusting various filtering methods using trackbars
* Authors : Mudit Jain & Dhaivat Bhatt
* Date: 20th December
*/

// Including the Libraries
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>

//Defining namespaces and variables

using namespace cv;
using namespace std;
Mat image,smoothened_image,thresholded_image;
int blur_filter_value = 5;
int selection_value=0;
int gaussian_filter_value=5;
int i=1;
int thresh_value=0;
int thresh_type=0;
int a=5;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

void Contours(int,void*);
//Defining the callback functions
//Median Filtering
void medianFiltering(int,void*)
{
  medianBlur(image,smoothened_image,2*(blur_filter_value)+3);
  imshow("output_image",smoothened_image);
}

//Gaussian Filtering
void gaussian_filter(int,void*)
{
  GaussianBlur( image,smoothened_image ,Size(2*i+1,2*i+1), 0, 0 );
  imshow("output_image",smoothened_image);
}


//Thresholding
void Threshold(int,void*)
{
  threshold( smoothened_image, thresholded_image, thresh_value,255,thresh_type );

  imshow( "thresholded_image", thresholded_image );
}

//Selection of the method for blurring
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
  namedWindow("thresholded_image",CV_WINDOW_AUTOSIZE);
  namedWindow("output_image",CV_WINDOW_AUTOSIZE);
  namedWindow("contours",CV_WINDOW_AUTOSIZE);
  createTrackbar("Selection","output_image",&selection_value,2,Selection);
  createTrackbar("Median_filtering","output_image",&blur_filter_value,10,medianFiltering);
  createTrackbar("Gaussian_filtering","output_image",&i,10,gaussian_filter);
  createTrackbar( "Threshold_type","thresholded_image", &thresh_type,4, Threshold );
  createTrackbar( "Threshold_value","thresholded_image", &thresh_value,255, Threshold );
Contours(0,0);
  createTrackbar( "contours_no." ,"contours", &a,contours.size(), Contours );

  //medianFiltering(0,0);
  while (true)
  {
    int c;
    c=waitKey(20);
    if((char)c==27)
    {break;}
  }
}

void Contours(int,void*)
{
  Mat drawing = Mat::zeros( image.size(), CV_8UC3 );
  findContours(smoothened_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  drawContours( drawing, contours, a, (0,255,0), 2, 8, hierarchy, 0, Point() );
  imshow( "contours",drawing);
}
