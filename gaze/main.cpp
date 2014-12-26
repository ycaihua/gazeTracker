
//Author Amit & Manasi


#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;



/*function Headers*/
void markerDetect(Mat image); //check this
void pupilDetect( Mat gray, Mat background);
void detectAndDisplay( Mat frame );

/*Global variables*/
	int iLowH = 0;
	int iHighH = 179;
	
	int iLowS = 0; 
	int iHighS = 255;
	
	int iLowV = 0;
	int iHighV = 255;

/*Function Definition*/
void markerDetect( Mat image)
{
	
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
	
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
	
	Moments mu;
	int xCen, yCen;

	Mat imgHSV;
	Mat imgThresholded;

	cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
	//Thresholding the image
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
      
	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	//morphological closing (fill small holes in the foreground)
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	mu = moments(imgThresholded);
	xCen = mu.m10/mu.m00;
	yCen = mu.m01/mu.m00;
	cout<<xCen<<"\t";
	cout<<yCen<<endl;

	imshow("Thresholded Image", imgThresholded); //show the thresholded image
	imshow("Original", image); //show the original image
			
}




/*void pupildetect(Mat frame, Mat background)
{

 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);
 int thresh=0;  // threshold variable for trackbar

	void onTrack(int)  // callback func for track bar
	{
		//cout<<thresh;
	}	
	//-- 1. Load the cascades
   
	   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eye\n"); return -1; };
	  if( !frame.empty() )
       { detectAndDisplay( frame ); }
       else
       { printf(" --(!) No captured frame -- Break!"); break; }

	void detectAndDisplay( Mat frame )
	{
	  vector<Rect> eyes;
	  Mat frame_gray;

	  cvtColor( frame, frame_gray, CV_BGR2GRAY );
	  equalizeHist( frame_gray, frame_gray );

	  //-- Detect eyes
		eyes_cascade.detectMultiScale( frame_gray, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );    
	
    

		    for( size_t j = 0; j < eyes.size(); j++ )
		     {
			Mat eyeROI = frame_gray( eyes[j] );
		        Point center( eyes[j].x + eyes[j].width*0.5, eyes[j].y + eyes[j].height*0.5 );
		        int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
		        circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
	
	
	
			imshow("eyes", eyeROI);
			pupilDetect(eyeROI,frame_gray);
			//cout<< xmin;
			//cout<<ymin;
	 
		//-- Show what you got
  			imshow( window_name, frame );
			}
  
	}


}

*/






int main( int argc, char** argv )
{
 	VideoCapture cap(0); //capture the video from web cam
	if ( !cap.isOpened() )  // if not success, exit program
 	{
 	     cout << "Cannot open the web cam" << endl;
 	     return -1;
 	}

	while(true)
	{
		Mat imgOriginal;

	        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
	
	         if (!bSuccess) //if not success, break loop
	        {
	             cout << "Cannot read a frame from video stream" << endl;
	             break;
	        }
				
		markerDetect(imgOriginal);


	        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       			{
        		    cout << "esc key is pressed by user" << endl;
        		    break; 
       			}
		
		
	}

return 0;


}
