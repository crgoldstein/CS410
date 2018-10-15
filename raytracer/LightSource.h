/*
 * LightSource.h
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


#include <vector>
#include <Eigen/Dense>
#include <string>

using namespace std;

class LightSource {
public:
	LightSource();
	LightSource(string Driver);
	Eigen::Vector3f getBrightnessVector() ;
	Eigen::Vector3f  getXYZvector();
	virtual ~LightSource();


//private:
	//The first four values given are the x, y, z, and w coordinates of the light source in world coordinates.
	int x;
	int y;
	int z;

	//The fourth value w is generally one, but a zero indicates a light source at infinity in the direction specified by x, y, and z.
	int w;

	//The last three values indicate the red, green, and blue levels of the light source on a zero to one scale.
	float red;
	float green;
	float blue;


};

#endif /* LIGHTSOURCE_H_ */
