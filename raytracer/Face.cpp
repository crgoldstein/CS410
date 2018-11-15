/*
 * Face.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#include "Face.h"
#include "objFile.h"


Face::Face() {
	// TODO A
	    A = point();
		B = point();
		C = point();
		calulateNormal();

}

Face::Face(int i, int j, const point &a,  const point &B, const point &C, const Materials &M, bool isSmooth){
  OBJindex = i;
	FaceIndex = j;
	this->A = a;
	this->B = B;
	this->C = C;
	calulateNormal();
	Material = M;
	smooth = isSmooth;
//	modle = Modle;
}

void Face:: calulateNormal(){

	Eigen::Vector3d AB(A.getVector() - B.getVector());
	Eigen::Vector3d AC(A.getVector() - C.getVector());
	Eigen::Vector3d Normal = AB.cross(AC);
	Normal = Normal.normalized().eval();
	normal= Normal;
}


Eigen::Vector3d Face:: getNormal() {
	return normal;
}

void Face::setNormal(const Eigen::Vector3d  n){
	normal=n;
}

string Face::toString(){
	return "\n	OBJindex Index "+ to_string(OBJindex)  +"\n	FACEindex Index "+ to_string(FaceIndex) +"\n	point A: "+ A.toString()+"\n	point B: "+ B.toString() +"\n	point C: "+C.toString()
			+"\n	Normal "+ to_string(normal(0))+ " "+ to_string(normal(1))+ " "+ to_string(normal(2));
			//+"\n	Model "+ modle->toString() ;//+ "\n 	Materials :" + Material.toString();
}

int Face:: compare (const Face& f) {

if( A.compare(f.A) == 0 && B.compare(f.B) == 0 && C.compare(f.C) == 0  ){
	return 0;
}
else {
	return -1;
}

}
Face::~Face() {
	// TODO Auto-generated destructor stub
}
