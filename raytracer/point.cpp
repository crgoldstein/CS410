/*
 * point.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: clairegoldstein
 */

#include "point.h"

point::point() {
	this->x=0;
	this->y=0;
	this->z=0;

}
point::point( float X, float Y, float Z) {
	this->x=X;
	this->y=Y;
	this->z=Z;

}

float point:: getX(){
	return this->x;
}
float  point:: getY(){
	return this->y;
}
float point:: getZ(){
	return this->z;
}
Eigen::Vector3f point::getVector(){
	Eigen::Vector3f point;
	point << x,y,z;
	return point;
}

string point:: toString(){
	return "X "+ to_string(this->x) + ", Y "+ to_string(this->y) + ", Z "+ to_string(this->z);
}
point::~point() {
	// TODO Auto-generated destructor stub
}

