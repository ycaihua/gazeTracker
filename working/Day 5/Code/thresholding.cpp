#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
main(int argc, char** argv)
{
  char* Image_name=argv[1];
  Mat image;
  image = imread(Image_name,0);
  medianBlur(image,image,5);
  adaptiveThreshold(image,image,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,11,2);
  namedWindow( image, WINDOW_AUTOSIZE );


  imshow( imageName, thresholded_image );


  waitKey(0);

  return 0;
}
