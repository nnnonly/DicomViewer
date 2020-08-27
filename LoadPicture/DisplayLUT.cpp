#include "pch.h"
#include "DisplayLUT.h"

void DisplayLUT::loadPixel(int windowWidth, int windowCenter, const cv::Mat&img, cv::Mat& outputImage)
{
	float width = windowWidth * 255 / 4095.0;
	float center = (windowCenter + 1000) * 255 / 4095.0;
	int low = round(center - width / 2);
	int high = round(center + width / 2);
	if (low < 0)
	{
		low = 0;
	}
	if (low > 255)
	{
		low = 255;
	}
	if (high < 0)
	{
		high = 0;
	}
	if (high > 255)
	{
		high = 255;
	}


	//cv::namedWindow("Display window1", cv::WINDOW_AUTOSIZE);// Create a window for display.
	//cv::imshow("Display window1", img);                   // Show our image inside it.

	//cv::waitKey(0);

	outputImage = cv::Mat::zeros(img.rows, img.cols, img.type());

	uchar* imgData = img.data;
	uchar* outData = outputImage.data;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (imgData[i * img.rows + j] >= high)
			{
				outData[i * img.rows + j] = 255;
			}
			if (imgData[i * img.rows + j] <= low)
			{
				outData[i * img.rows + j] = 0;
			}
			if (imgData[i * img.rows + j] > low && imgData[i * img.rows + j] < high)
			{
				int p = (imgData[i * img.rows + j] - low) * 255 / width;
				if (p > 255)
				{
					outData[i * img.rows + j] = 255;
				}
				else if (p < 0)
				{
					outData[i * img.rows + j] = 0;
				}
				else {
					outData[i * img.rows + j] = p;
				}
			}
		}
	}



	//cv::namedWindow("Output window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	//cv::imshow("Output window", outputImage);                   // Show our image inside it.
}
