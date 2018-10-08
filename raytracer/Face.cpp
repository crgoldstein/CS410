/*
 * Face.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#include "Face.h"


Face::Face() {
	// TODO Auto-generated constructor stub
	    this->A=point();
		this->B=point();
		this->C=point();
		calulateNormal();
		this->Materials ="NULL";
}

Face::Face(point A, point B,point C,string Materials){
	this->A=A;
	this->B=B;
	this->C=C;
	calulateNormal();
	this->Materials = Materials;
}

void Face:: calulateNormal(){
	Eigen::Vector3f AB =A.getVector() - B.getVector() ;
	Eigen::Vector3f AC =A.getVector() - C.getVector() ;
	Eigen::Vector3f Normal = AB.cross(AC);
	Normal = Normal.normalized().eval();
	this->normal=Normal;
}

Eigen::Vector3f Face:: getNormal(){
	return this->normal;
}

string Face::toString(){
	return " point A: "+ A.toString()+"\n point B: "+ B.toString() +"\n point C: "+C.toString() + "\n Material:" + this->Materials;
}

Face::~Face() {
	// TODO Auto-generated destructor stub
}

