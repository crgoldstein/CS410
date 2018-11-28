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
	Materials(vector<double> SphereInfo);
	Materials(string fileName);
	virtual ~Materials();
	string toString();
	Eigen::Vector3d getKaVector();
	Eigen::Vector3d getKdVector();
	Eigen::Vector3d getKsVector();


	double phong;

	double KaRed	;
	double KaGreen;
	double KaBlue;

	double KdRed;
	double KdGreen;
	double KdBlue;

	double KsRed;
	double KsGreen;
	double KsBlue;

	double KrRed;
	double KrGreen;
	double KrBlue;

	double KoRed;
	double KoGreen;
	double KoBlue;

	double Eta;

};

#endif /* MATERIALS_H_ */
