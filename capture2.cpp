#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// See www.asciitable.com
#define ESCAPE_KEY (27)
#define SYSTEM_ERROR (-1)
int main()
{
   VideoCapture cam0(0);
   namedWindow("video_display");
   	char winInput;	
   if (!cam0.isOpened())
   {
       exit(SYSTEM_ERROR);
   }

 
 cam0.set(CAP_PROP_FRAME_WIDTH, 640);
 cam0.set(CAP_PROP_FRAME_HEIGHT, 480);
while (1)
      {
        Mat frame;
	Mat frame_colour_P;
      	Mat frame_colour;
      	Mat frame_canny; 
	cam0.read(frame);


	// Edge detection
    	Canny(frame, frame_canny, 50, 200, 3);
    	// Copy edges to the images that will display the results in BGR
    	cvtColor(frame_canny, frame_colour, COLOR_GRAY2BGR);
    	frame_colour_P = frame_colour.clone();
    	// Standard Hough Line Transform
    	vector<Vec2f> lines; // will hold the results of the detection
    	HoughLines(frame_canny, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection

	for( size_t i = 0; i < lines.size(); i++ )
    	{
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( frame_colour, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    	}
	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(frame_canny, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
	// Draw the lines
    	for( size_t i = 0; i < linesP.size(); i++ )
    	{
        	Vec4i l = linesP[i];
        	line( frame_colour_P, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    	}
	imshow("Source", frame);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", frame_colour);
    	imshow("Detected Lines (in red) - Probabilistic Line Transform", frame_colour_P);
    	// Wait and Exit

	if ((winInput = waitKey(10)) == ESCAPE_KEY)
        {
         break;
        }
	
}
};


