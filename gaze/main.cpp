
//Author Amit & Manasi
#include <iostream>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

/*function Headers*/
int markerDetect(Mat image); //check this
int pupilDetect( Mat eyeROI);
void detectAndDisplay( Mat frame );

/*Global variables*/
int iLowH = 0;
int iHighH = 179;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;

int thresh=0;  // threshold variable for trackbar
int flag=0;  // to return from function marker Detect
int calibration_pts=2;

/*Function Definition*/

void onTrack(int)  // callback func for track bar
	{
		//cout<<thresh;
	}

int markerDetect( Mat image)  // used to detect the marker placed on forhead for gaze vector quantification
	{
		Moments mu;
		int xCen, yCen;

		Mat imgHSV;
		Mat imgThresholded;
		cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		//Thresholding part starts

		//Thresholding the image
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

		//Centroid calculation starts

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

		//Centroid calculation ends


		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", image); //show the original image

		return xCen,yCen;

	}

int pupilDetect(Mat frame)
	{
		Mat frame_gray;  // gray_scale image
		string window_name = "Capture - Face detection";
		vector<Rect> eyes;  // vector of segmented eyes
		Mat eyeROI;   		// Region of interesti.e. eyes
		Moments mu;
		int xCen;
		int yCen;
		// RNG rng(12345);

		if( !frame.empty() )
		{
			cvtColor( frame, frame_gray, CV_BGR2GRAY );
			equalizeHist( frame_gray, frame_gray );   // pre processing

			//-- 1. Load the cascades
			String eyes_cascade_name = "../config/haarcascade_eye_tree_eyeglasses.xml";
			CascadeClassifier eyes_cascade;

			if( !eyes_cascade.load( eyes_cascade_name ) )
			{
				printf("--(!)Error loading eye\n");
			}

			//-- Detect eyes
			eyes_cascade.detectMultiScale( frame_gray, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

			for( size_t j = 0; j < eyes.size(); j++ )     //draw circle around every detected eye
			{
				eyeROI = frame_gray( eyes[j] );
				Point center( eyes[j].x + eyes[j].width*0.5, eyes[j].y + eyes[j].height*0.5 );
				int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
				circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
				imshow("original image",frame);
				imshow("eyes", eyeROI);



				cv::threshold(eyeROI, eyeROI, thresh, 255, cv::THRESH_BINARY);

				//morphological opening (remove small objects from the foreground)
				erode(eyeROI, eyeROI, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				dilate( eyeROI, eyeROI, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

				//morphological closing (fill small holes in the foreground)
				dilate( eyeROI, eyeROI, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				erode(eyeROI, eyeROI, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

				mu = moments(eyeROI);
				xCen = mu.m10/mu.m00;
				yCen = mu.m01/mu.m00;
				cout<<xCen<<"\t";
				cout<<yCen<<endl;

				cv::imshow("eyeROI", eyeROI);

				//cout<< xmin;
				//cout<<ymin;
				return xCen,yCen;
				//-- Show what you got
				imshow( window_name, frame );
			 }

		}
		else
		{
			printf(" --(!) No frame loaded(!)--");
		}

	}


int main( int argc, char** argv )
	{
		int mx,my=0;
		int px,py=0;
		VideoCapture cap(0); //capture the video from web cam
		Mat imgOriginal;     //image object
		int vx[2]={0};
		int vy[2]={0};

		if ( !cap.isOpened() )  // if not success, exit program
		{
			cout << "Cannot open the web cam" << endl;
			return -1;
		}

		while(true)    // marker detection
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



			if (flag==0)
				{
					mx,my = markerDetect(imgOriginal);
				}
			//Closing all the windows
			else if (flag==1)
				{
				destroyWindow("Control");
				destroyWindow("Thresholded Image");
				destroyWindow("Original");
				cout << mx << " " << my << endl;  //print the centrois of marker
				flag=0;
				break;
				}


			if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				break;
			}
		}

		while(true)   // pupil thresholding
		{
			bool bSuccess = cap.read(imgOriginal); // read a new frame from video

			if (!bSuccess) //if not success, break loop
			{
			cout << "Cannot read a frame from video stream" << endl;
			break;
			}
			namedWindow("pupil Thresholding",CV_WINDOW_AUTOSIZE);
			cvCreateTrackbar("Thresh", "pupil Thresholding", &thresh, 255,onTrack); // create a trackbar for pupil thresholding - grayThreshold (0 - 255)
			cvCreateTrackbar("finalize", "pupil Thresholding", &flag, 1);

			if(flag==0)
			px,py = pupilDetect(imgOriginal);
			else
			{
			destroyWindow("pupil Thresholding");
			destroyWindow("eyes");
			destroyWindow("eyeROI");
			destroyWindow("original image");
			cout << px << " " << py << endl;
			flag=0;
			break;
			}

			if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				break;
			}

		}


		for(int i=0;i<calibration_pts;i++)
		{

			while(true)
			{
					bool bSuccess = cap.read(imgOriginal); // read a new frame from video
					if (!bSuccess) //if not success, break loop
					{
						cout << "Cannot read a frame from video stream" << endl;
						break;
					}

			namedWindow("calibration1",CV_WINDOW_AUTOSIZE);
			cvCreateTrackbar("finalize", "calibration1", &flag, 1,onTrack); // create a trackbar for pupil thresholding - grayThreshold (0 - 255)

			if (flag==0)
			{
				px,py = pupilDetect(imgOriginal);
				vx[i] = mx - px;
				vy[i] = my - py;
				cout << "vx[i] : " << vx[i] << " " << "vy[i] : " <<  vy[i] << endl;
			}
			else
			{
				break;
			}
		}

	}
	return 0;
	}
