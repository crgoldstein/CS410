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
#include "objFile.h"
#include <string>

using namespace std;



class Ray {
public:
	Ray();
	Ray(const Eigen::Vector3d &P, const Eigen::Vector3d &D);
	virtual ~Ray();

	double RayTriangleInterection(Face &f);
	double RaySphereInterection(Sphere &S);
	bool RayModleInterection(objFile &M);


	string toString();

	Eigen::Vector3d pointL;
	Eigen::Vector3d Direction;

	double minTface;//
	double minGamma ;
	double	minBeta ;
	Face closestFace;
	objFile closestModel;

	double minTsphere;//
	Sphere ClosestSphere;

};

#endif /* RAY_H_ */
