/*
 * point.h
 *
 *  Created on: Oct 8, 2018
 *      Author: clairegoldstein
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
//#include "Face.h"

using namespace std;

class point {

public:
	point();

	point(const double X, const double Y, const double Z);
	virtual ~point();
	Eigen::Vector3d getVector();
	//vector<Face> VerticesFaces;
	double getX();
	double getY();
	double getZ();
	string toString();
	point Vector2Point(const Eigen::Vector3d &v);



private:
	double x,y,z;

};

#endif /* POINT_H_ */
