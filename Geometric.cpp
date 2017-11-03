#include "Geometric.h"
#include "Piece.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <algorithm>
using namespace std;
using namespace cv;

geometric::Point geometric::Point::operator+(const Point& other)
{
	return geometric::Point(this->x + other.x, this->y + other.y);
}

geometric::Point geometric::Point::operator-(const Point& other)
{
	return geometric::Point(this->x - other.x, this->y - other.y);
}

int geometric::Point::operator*(const Point& other)
{
	return this->x * other.x + this->y * other.y;
}

bool geometric::Point::operator==(const Point &other)
{
	return (x == other.x) && (y == other.y);
}

double geometric::Point::length()
{
	return sqrt(x * x + y * y);
}

geometric::Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool geometric::Point::rotate(double angle, Point center)
{
	Point tmp = *this - center;

	double c = cos(angle);
	double s = sin(angle);

	double xnew = tmp.x * c - tmp.y * s;
	double ynew = tmp.x * s + tmp.y * c;

	if (!equal(xnew, round(xnew)) || !equal(ynew, round(ynew))) return false;

	x = round(xnew) + center.x;
	y = round(ynew) + center.y;
	return true;
}

void geometric::Point::print()
{
	cout << x << " " << y << " ";
}

int geometric::orientation(const Point& A, const Point& O, const Point& B)
{
	// result: < 0 if clockwise, > 0 if counter clockwise, == 0 if collinear.
	int val = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	if (val == 0) return val;
	return val / abs(val);
}

double geometric::compute_angle(Point A, Point O, Point B)
{
	if ((A == O) || (B == O)) return 0;
	geometric::Point vOA = A - O;
	geometric::Point vOB = B - O;
	double dOA = vOA.length();
	double dOB = vOB.length();
	double res = acos((vOA * vOB) / (dOA * dOB));

	int c = geometric::orientation(A, O, B);
	if (c > 0) res = 2 * PI - res;
	return res;
}

bool geometric::onSegment(Point p, Point q, Point r)
{
	// return true if q lies on line segment pr
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

bool geometric::equal(double d, double e)
{
	return abs(d - e) < 1e-6;
}

bool geometric::intersect(const Point & a1, const Point & b1, const Point & a2, const Point & b2)
{
	int o1 = orientation(a1, b1, a2);
	int o2 = orientation(a1, b1, b2);
	int o3 = orientation(a2, b2, a1);
	int o4 = orientation(a2, b2, b1);
	if ((o1 == 0) || (o2 == 0) || (o3 == 0) || (o4 == 0))
		return false;
	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}

bool geometric::check_polygon_intersect(const Piece & a, const Piece & b)
{
	//note: not 100% accurate in exchange for speed
	//future update: may use clipper library
	vector<cv::Point2i> a_vert, b_vert;

	for (int i = 0; i < a.vertices.size(); i++)
		a_vert.push_back(cv::Point2i(a.vertices[i].point.x, a.vertices[i].point.y));

	for (int i = 0; i < b.vertices.size(); i++)
		b_vert.push_back(cv::Point2i(b.vertices[i].point.x, b.vertices[i].point.y));
	
	for (int i = 0; i < a_vert.size(); i++)
	{
		int test = cv::pointPolygonTest(b_vert, a_vert[i], false);
		if (test == 0) continue;
		if ((test > 0) ^ b.is_frame)
			return true;
	}
	for (int i = 0; i < b_vert.size(); i++)
	{
		int test = cv::pointPolygonTest(a_vert, b_vert[i], false);
		if (test == 0) continue;
		if ((test > 0) ^ a.is_frame)
			return true;
	}

	for (int i = 0; i < a.vertices.size(); i++)
		for (int j = 0; j < b.vertices.size(); j++)
			if (intersect(a.vertices[i].point, a.vertices[i].next()->point, b.vertices[j].point, b.vertices[j].next()->point))
				return true;

	return false;
}

vector<cv::Point> toVectorPoint(vector<Vertex>& vertex, int ratio) {
	vector<cv::Point> vtmp;
	vtmp.clear();
	for each (Vertex v in vertex)
	{
		vtmp.push_back(cv::Point(v.point.x*ratio, v.point.y*ratio));
	}
	return vtmp;
}

Mat geometric::drawPiece(Piece& p, int ratio) {
	Mat res;
	vector<cv::Point> vtmp;
	vtmp.clear();
	if (p.vertices.size() != 0) {
		vtmp = toVectorPoint(p.vertices, ratio);
		Rect bound = boundingRect(vtmp);
		vector<vector<cv::Point>> a;
		a.clear();
		vector<cv::Point> pnt;
		a.push_back(pnt);
		for each (cv::Point point in vtmp)
		{
			a.at(0).push_back(cv::Point(point.x - bound.x, point.y - bound.y));
		}
		res = Mat(bound.height, bound.width, CV_8UC3, Scalar(255, 255, 255));
		fillPoly(res, a, Scalar(0, 0, 255));
		return res;
	}
	return Mat(10,10, CV_8UC3, Scalar(255, 255, 255));
}