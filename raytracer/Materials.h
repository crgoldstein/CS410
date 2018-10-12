/*
 * Materials.h
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <string>

using namespace std;

class Materials {

public:
	Materials();
	Materials(string fileName);
	virtual ~Materials();
	string toString();
	Eigen::Vector3f getKaVector();
	Eigen::Vector3f getKdVector();
	Eigen::Vector3f getKsVector();


	float KaRed	;
	float KaGreen;
	float KaBlue;

	float KdRed;
	float KdGreen;
	float KdBlue;

	float KsRed;
	float KsGreen;
	float KsBlue;

};

#endif /* MATERIALS_H_ */
