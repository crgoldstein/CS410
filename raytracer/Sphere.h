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

class Sphere {

public:
	Sphere();
	Sphere( const string Driver);
	string toString();
	virtual ~Sphere();


	point Center;
	double radius ;
	Materials Material;

};

#endif /* SPHERE_H_ */
