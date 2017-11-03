#pragma once
#define PI 3.14159265358979323846
#define COLLINEAR 0
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

class Piece;
namespace geometric
{
	class Point
	{
	public:
		int x, y;
		Point(int x = 0, int y = 0);
		Point operator+(const Point&);
		Point operator-(const Point&);
		int operator*(const Point&);
		bool operator==(const Point&);
		double length();
		bool rotate(double angle, Point center);
		void print();
	};

	int orientation(const Point& A, const Point& O, const Point& B);
	double compute_angle(Point A, Point O, Point B);
	bool onSegment(Point p, Point q, Point r);
	bool equal(double d, double e);
	bool intersect(const Point& a1, const Point& b1, const Point& a2, const Point& b2);
	bool check_polygon_intersect(const Piece& a, const Piece& b);
	Mat drawPiece(Piece& p, int ratio);
}