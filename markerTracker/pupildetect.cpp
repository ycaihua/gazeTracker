 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;

 /** Function Headers */
 void detectAndDisplay( Mat frame );
 void pupilDetect( Mat gray, Mat background);
 /** Global variables */
 String face_cascade_name = "haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);


 /** @function main */
 int main( int argc, const char** argv )
 {
	
   CvCapture* capture;
   Mat frame;

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loadings face\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eye\n"); return -1; };

   //-- 2. Read the video stream
   capture = cvCaptureFromCAM( -1 );
   if( capture )
   {
     while( true )
     {
   frame = cvQueryFrame( capture );
	Size s=frame.size();
	int rows = s.height;
	int column = s.width;
	//cout<< rows;
	//cout<<column;
   //-- 3. Apply the classifier to the frame
       if( !frame.empty() )
       { detectAndDisplay( frame ); }
       else
       { printf(" --(!) No captured frame -- Break!"); break; }

       int c = waitKey(10);
       if( (char)c == 'c' ) { break; }
      }
   }
   return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  vector<Rect> faces;
  Mat frame_gray;
//	Mat leye = Mat::zeros(frame_gray.size(),CV_8UC1);
//	Mat reye = Mat::zeros(frame_gray.size(),CV_8UC1);
  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       //circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
	//Rect roi = boundingRect(contours_final[i]);
	int xmin= center.x-radius;
	int xmax= center.x+radius;
	int ymin = center.y-radius;
	int ymax=center.y+radius;
	//Point p1(xmin,ymin);
	//Point p3(xmax,ymax);
	//Point p2(xmin,ymax);
	//Point p4(xmax,ymin);
	//rectangle(frame,p1,p2,255,1);
	if(ymax<240)
	{
		Mat lefteyes (frame_gray, Rect(xmin, ymin, 2*radius, 2*radius) );
		imshow("leyes", lefteyes);
		pupilDetect(lefteyes,frame_gray);
	//cout<< xmin;
	//cout<<ymin;
	}
	else
	{
		Mat reyes (frame_gray, Rect(xmin, ymin, 2*radius, 2*radius) );
		imshow("reyes", reyes);
		pupilDetect(reyes, frame);
	}
 
//-- Show what you got
  imshow( window_name, frame );
	}
  }
}
void pupilDetect(Mat gray, Mat background)
{
	Moments mu;	
	int xCen;
	int yCen;	
	// Convert to binary image by thresholding it
	cv::threshold(gray, gray, 150, 255, cv::THRESH_BINARY);	
	// Find all contours
	//vector<std::vector<cv::Point> > contours;
	//morphological opening (remove small objects from the foreground)
	erode(gray, gray, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	dilate( gray, gray, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	//morphological closing (fill small holes in the foreground)
	dilate( gray, gray, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	erode(gray, gray, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	mu = moments(gray);
	xCen = mu.m10/mu.m00;
	yCen = mu.m01/mu.m00;
	cout<<xCen<<"\t";
	cout<<yCen<<endl;
	//findContours(gray.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	// Fill holes in each contour
	//drawContours(gray, contours, -1, CV_RGB(255,255,255), -1);
	//for (int i = 0; i < contours.size(); i++)
	//{
	//	double area = cv::contourArea(contours[i]);
	//	Rect rect = cv::boundingRect(contours[i]);
	//	int radius = rect.width/2;

	// If contour is big enough and has round shape
	// Then it is the pupil
	//if (area >= 20 &&
	//std::abs(1 - ((double)rect.width / (double)rect.height)) <= 0.3 && std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
	//	{
	//	cv::circle(background, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 2);
	//	Point pupilcenter(rect.x + radius, rect.y + radius);
	//	cout<<pupilcenter;
	//	}
	//}
	cv::imshow("image", gray);
}

  


