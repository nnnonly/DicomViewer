#include "pch.h"
#include "Vector.h"

#include "pch.h"
#include "Vector.h"]
#define PI 3.14159265


double Vector::distance(const cv::Point2f &A, const cv::Point2f &B)
{
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}

double Vector::aCos(const cv::Point2f &A, const cv::Point2f &B, const cv::Point2f &C)
{
	double vectorABx = A.x - B.x;
	float vectorABy = A.y - B.y;

	double vectorBCx = B.x - C.x;
	double vectorBCy = B.y - B.y;

	double lengthAB = distance(A, B);
	double lengthBC = distance(B, C);

	double cos = abs(vectorABx * vectorBCx + vectorABy * vectorBCy) / (lengthAB * lengthBC);
	double abc = abs(acos(cos) * 180 / PI);

	return abs(acos(cos) * 180 / PI);
}

