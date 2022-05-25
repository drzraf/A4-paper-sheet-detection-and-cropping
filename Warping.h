/*
#  File        : Warping.h
#  Description : Perspective transformation of 2D image
#  Copyright   : HYPJUDY 2017/4/6
#  Details     : https://hypjudy.github.io/2017/03/28/cvpr-A4-paper-sheet-detection-and-cropping/
#  Code        : https://github.com/HYPJUDY/A4-paper-sheet-detection-and-cropping
*/

#pragma once
#ifndef _Warping_
#define _Warping_
#include "Hough.h"

#ifdef Success
  #undef Success
#endif

#include <eigen3/Eigen/Dense>

class Warping {
private:
	CImg<float> dest_A4; // 210mm*297mm -> 410*594
	CImg<float> src;

	float x1, y1, x2, y2, x3, y3, x4, y4; // source corners
	float a, b, c, d, e, f, m, l; // parameters

	void perspectiveTransform();
	float getXTransformInv(int u, int v);
	float getYTransformInv(int u, int v);
	void reverseMapping();
	float bilinearInterpolate(float x, float y, int z);
	void mapping(float x, float y);
public:
	Warping(Hough hough2);
	CImg<float> getCroppedImg() { return dest_A4; }
};

#endif
