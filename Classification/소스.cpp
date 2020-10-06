#include "opencv2/opencv.hpp" 
#include <iostream>  
#include <string> 

using namespace cv;
using namespace std;


void Label(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 1;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}



int main(int, char**)
{
	Mat input, result, gray;

	input = imread("triangle2.jpg", IMREAD_COLOR); //Load Image
	if (input.empty())
	{
		cout << "Error" << std::endl;
		return -1;
	}


	cvtColor(input, gray, COLOR_BGR2GRAY); //GrayScale

	Mat binary_image;
	threshold(gray, gray, 125, 255, THRESH_BINARY_INV | THRESH_OTSU); //Binarization


	vector<vector<Point> > contours;
	findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); //Find Contour

	vector<Point2f> approx; //Approximation Contour
	result = input.clone();

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

		if (fabs(contourArea(Mat(approx))) > 100)  // Area Size > 100
		{

			int size = approx.size();

			// Draw approximate line
			if (size % 2 == 0) { 
				line(result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(result, approx[k], 3, Scalar(0, 0, 255));
			}
			else {
				line(result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(result, approx[k], 3, Scalar(0, 0, 255));
			}


			//Define Circle or Triangle
			if (size == 3)
				Label(result, "triangle", contours[i]);

			else if (size == 8 && isContourConvex(Mat(approx)))
				Label(result, "circle", contours[i]); 


		}

	}


	imshow("input", input);
	imshow("result", result);


	waitKey(0);

	return 0;
}

