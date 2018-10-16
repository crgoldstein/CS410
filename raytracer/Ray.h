/*
 * Ray.h
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#ifndef RAY_H_
#define RAY_H_

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include "point.h"
#include <string>

using namespace std;



class Ray {
public:
	Ray();
	Ray(const Eigen::Vector3f &P, const float t, const Eigen::Vector3f &D);
	virtual ~Ray();
	Eigen::Vector3f getRayVector();
	string toString();

	Eigen::Vector3f Pixel;
	float T;
	Eigen::Vector3f Direction;
};

#endif /* RAY_H_ */
