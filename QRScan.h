#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "zbar.h"
#include <iostream>
using namespace std;
using namespace cv;
using namespace zbar;
vector<String> ScanQR(VideoCapture& cap) {
	vector<String> res = vector<String>();
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	int width = (int)cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	Mat frame,grayFrame;
	//frame = imread("test.jpg", 1);
	
	do {
		cap >> frame;
		//frame = imread("test.jpg", 1);
		if (frame.data == NULL) break;
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		uchar *raw = (uchar *)grayFrame.data;
		// wrap image data  
		Image image(width, height, "Y800", raw, width * height);
		// scan the image for barcodes  
		int n = scanner.scan(image);
		// extract results  
		for (Image::SymbolIterator symbol = image.symbol_begin();
			symbol != image.symbol_end();
			++symbol) {
			string symbolData = symbol->get_data();
			bool chuaxuathien = true;
			for each (String str in res)
			{
				if (symbolData == str) {
					chuaxuathien = false;
					break;
				}
			}
			if (chuaxuathien) {
				cout <<"QR code:"<< symbolData <<endl; 
				res.push_back(symbolData);
					}

			vector<Point> vp;
			int n = symbol->get_location_size();
			for (int i = 0; i<n; i++) {
				vp.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
			}
			RotatedRect r = minAreaRect(vp);
			Point2f pts[4];
			r.points(pts);
			for (int i = 0; i<4; i++) {
				line(frame, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 3);
			}
		}
		putText(frame, to_string(res.size()) + " QR has been added!!", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
		imshow("Display", frame);
		image.set_data(NULL, 0);
	} while (waitKey(1) != 13);

	if (res.size() == 0) res.push_back("");
	return res;
}



