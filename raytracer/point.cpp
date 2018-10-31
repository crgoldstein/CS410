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
point::point( const double X, const double Y, const double Z) {
	this->x=X;
	this->y=Y;
	this->z=Z;

}

double point:: getX(){
	return this->x;
}
double  point:: getY(){
	return this->y;
}
double point:: getZ(){
	return this->z;
}

point point:: Vector2Point(const Eigen::Vector3d &v){

	point X(v(0),v(1),v(2));
	return X;
}

Eigen::Vector3d point::getVector(){
	Eigen::Vector3d point(x,y,z);
	return point;
}

string point:: toString(){
	return "X "+ to_string(this->x) + ", Y "+ to_string(this->y) + ", Z "+ to_string(this->z);
}

point::~point() {
	// TODO Auto-generated destructor stub
}
