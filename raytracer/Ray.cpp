/*
 * Ray.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#include "Ray.h"

Ray::Ray(){
		Pixel = point();
		T = 0;
		Direction = point();
}

Ray::Ray(point P, float t, point D) {
	Pixel = P;
	T = t;
	Direction = P;

}

Eigen::Vector3f Ray:: getRayVector(){
	Eigen::Vector3f  ray;
	ray = Pixel.getVector() + (T*Direction.getVector());
	return ray;
}


string Ray::toString(){
	//return "Pixel  " + Pixel.toString() +" T "+ to_string(T) +  "Direction  " << Direction.toString() ;
 return "";
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

