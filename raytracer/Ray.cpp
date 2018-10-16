/*
 * Ray.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#include "Ray.h"

Ray::Ray(){
		Pixel << 0,0,0;
		T = 0;
		Direction  << 0,0,0;
}

Ray::Ray(const Eigen::Vector3f &P, const float t, const Eigen::Vector3f &D) {
	Pixel = P;
	T = t;
	Direction = P;

}

Eigen::Vector3f Ray:: getRayVector(){
	Eigen::Vector3f ray(Pixel+ (T*Direction));
	return ray;
}


string Ray::toString(){
	//return "Pixel  " + Pixel.toString() +" T "+ to_string(T) +  "Direction  " << Direction.toString() ;
 return "";
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

