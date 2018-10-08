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

	point(float X, float Y, float Z);
	virtual ~point();
	Eigen::Vector3f getVector();
	float getX();
	float getY();
	float getZ();
	string toString();

private:
	float x,y,z;

};

#endif /* POINT_H_ */
