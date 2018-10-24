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
#include <vector>

using namespace std;

class Materials {

public:
	Materials();
	Materials(vector<float> SphereInfo);
	Materials(string fileName);
	virtual ~Materials();
	string toString();
	Eigen::Vector3f getKaVector();
	Eigen::Vector3f getKdVector();
	Eigen::Vector3f getKsVector();


	float phong;

	float KaRed	;
	float KaGreen;
	float KaBlue;

	float KdRed;
	float KdGreen;
	float KdBlue;

	float KsRed;
	float KsGreen;
	float KsBlue;

	float KrRed;
	float KrGreen;
	float KrBlue;

};

#endif /* MATERIALS_H_ */
