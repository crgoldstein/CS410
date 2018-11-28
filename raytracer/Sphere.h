/*
 * Sphere.h
 *
 *  Created on: Oct 22, 2018
 *      Author: clairegoldstein
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <string>
#include <iostream>
#include "Materials.h"
#include "point.h"

using namespace std;
class Ray;
class Sphere {

public:
	Sphere();
	Sphere( const string Driver);
	string toString();
	virtual ~Sphere();

	Ray refract_exit(	Eigen::Vector3d W, Eigen::Vector3d pt, double eta_inside);
	Eigen::Vector3d refract_tray(Eigen::Vector3d W,	Eigen::Vector3d  pt, Eigen::Vector3d  Normal, double eta1, double eta2); //Snell's Law

	point Center;
	double radius ;
	Materials Material;

};

#endif /* SPHERE_H_ */
