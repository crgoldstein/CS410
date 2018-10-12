/*
 * AmbientLight.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#include "AmbientLight.h"


#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <string>


#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

using namespace std;

AmbientLight::AmbientLight() {
	red=0;
	green=0;
	blue=0;

}


AmbientLight::AmbientLight(string Driver){
		vector<string> line;
		boost::split(line, Driver ,boost::is_any_of(" "));

		red =stof((line[1]).c_str(),0);
	 	green = stof((line[2]).c_str(),0);
		blue = stof((line[3]).c_str(),0);
}


Eigen::Vector3f AmbientLight:: getVector(){
	Eigen::Vector3f vec;
	 vec << red, green, blue;
	 return vec;

}


AmbientLight::~AmbientLight() {
	// TODO Auto-generated destructor stub
}

