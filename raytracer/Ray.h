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
	Ray(const point P, const float t, const point D);
	virtual ~Ray();
	Eigen::Vector3f getRayVector();
	string toString();

	point Pixel;
	float T;
	point Direction;
};

#endif /* RAY_H_ */
