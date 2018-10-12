/*
 * Face.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#include "Face.h"



Face::Face() {
	// TODO Auto-generated constructor stub
	    A=point();
		B=point();
		C=point();
		calulateNormal();
		//Material= Materials M;
}

Face::Face(point A, point B,point C, Materials M){
	this->A=A;
	this->B=B;
	this->C=C;
	calulateNormal();
	Material=M;
}

void Face:: calulateNormal(){

	Eigen::Vector3f AB =   B.getVector() - A.getVector();
	Eigen::Vector3f AC =   C.getVector() - A.getVector();
	Eigen::Vector3f Normal = AB.cross(AC);
	Normal = Normal.normalized().eval();
	normal= Normal;
}


Eigen::Vector3f Face:: getNormal(){
	return normal;
}

void Face::setNormal( Eigen::Vector3f  n){
	normal=n;
}

string Face::toString(){
	return " point A: "+ A.toString()+"\n point B: "+ B.toString() +"\n point C: "+C.toString()
			+"\n Normal "+ to_string(normal(0))+ " "+ to_string(normal(1))+ " "+ to_string(normal(2));
			//+ "\n 	Materials :" + Material.toString();
}


Face::~Face() {
	// TODO Auto-generated destructor stub
}

