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

using namespace std;

class point {

public:
	point();
	point(const double X, const double Y, const double Z, const double Index);
	point( const double X, const double Y, const double Z);
	double getX();
	double getY();
	double getZ();
	Eigen::Vector3d getVector();
	vector<int> VerticesFaces;
	void AddFace(int);

	string toString();
	point Vector2Point(const Eigen::Vector3d &v);

	virtual ~point();

private:
	double x,y,z,index;

};

#endif /* POINT_H_ */
