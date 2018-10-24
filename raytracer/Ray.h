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
#include "Face.h"
#include "Sphere.h"
#include <string>

using namespace std;



class Ray {
public:
	Ray();
	Ray(const Eigen::Vector3f &P, const Eigen::Vector3f &D);
	virtual ~Ray();

	float RayTriangleInterection(Face &f);
	float  RaySphereInterection(Sphere &S);


	string toString();

	Eigen::Vector3f Pixel;
	Eigen::Vector3f Direction;

	float minTface;//
	Face closestFace;

	float minTsphere;//
	Sphere ClosestSphere;

};

#endif /* RAY_H_ */
