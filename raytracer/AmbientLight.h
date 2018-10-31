/*
 * AmbientLight.h
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#ifndef AMBIENTLIGHT_H_
#define AMBIENTLIGHT_H_

#include <vector>
#include <Eigen/Dense>
#include <string>

using namespace std;

class AmbientLight {

public:
	AmbientLight();
	AmbientLight(string &Driver);
	Eigen::Vector3d getVector();
	virtual ~AmbientLight();

//private:
	double red ;
	double green ;
	double blue ;

};

#endif /* AMBIENTLIGHT_H_ */
