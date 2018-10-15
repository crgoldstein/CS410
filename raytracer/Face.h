/*
 * Face.h
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#ifndef FACE_H_
#define FACE_H_

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include "point.h"
#include "Materials.h"
#include <string>

using namespace std;

class Face {
public:
	Face();
	Face(const point &a ,const point &B, const point &C, const Materials &M); //??? Wont let me pass by &
	void calulateNormal();
	Eigen::Vector3f getNormal() ;
	void setNormal(const Eigen::Vector3f n);
	virtual ~Face();
	string toString();


	point A;
	point B;
	point C;
	Materials Material;
	Eigen::Vector3f normal;


};

#endif /* FACE_H_ */
