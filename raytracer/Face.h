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
#include <string>

using namespace std;

class Face {
public:
	Face();
	Face(point A, point B, point C, string Materials);
	void calulateNormal();
	Eigen::Vector3f getNormal();
	virtual ~Face();
	string toString();



	point A;
	point B;
	point C;
	string Materials;
	Eigen::Vector3f normal;


};

#endif /* FACE_H_ */
