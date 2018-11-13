/*
 * point.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: clairegoldstein
 */
#include "point.h"
#include "Face.h"

point::point() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->index =-1;
	VerticesFaces = vector<int>();

}
point::point( const double X, const double Y, const double Z){
		this->x = X;
		this->y = Y;
		this->z = Z;
		VerticesFaces = vector<int>();
		this->index =-1;
}
point::point( const double X, const double Y, const double Z,const double Index) {
	this->x = X;
	this->y = Y;
	this->z = Z;
	VerticesFaces = vector<int>();
	this->index =Index;

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

void point:: AddFace(int i){
	VerticesFaces.push_back(i);
}

string point:: toString(){
	return "index "+ to_string(this->index)+"X "+ to_string(this->x) + ", Y "+ to_string(this->y) + ", Z "+ to_string(this->z)
			+ ", VerticesFaces.size() "+to_string(VerticesFaces.size());
}

point::~point() {
	// TODO Auto-generated destructor stub
}
