/*
 * LightSource.cpp
 *
 *  Created on: Oct 7, 2018
 *      Author: clairegoldstein
 */

#include "LightSource.h"

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <string>


#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

using namespace std;

LightSource::LightSource() {
	// TODO Auto-generated constructor stub

}


LightSource::LightSource(string &Driver){
			vector<string> line;
			boost::split(line, Driver ,boost::is_any_of(" "));

			x =stof((line[1]).c_str(),0);
			y = stof((line[2]).c_str(),0);
			z = stof((line[3]).c_str(),0);
			w = stof((line[4]).c_str(),0);

			red =stof((line[5]).c_str(),0);
		 	green = stof((line[6]).c_str(),0);
			blue = stof((line[7]).c_str(),0);
}

Eigen::Vector3f LightSource:: getBrightnessVector() {

	Eigen::Vector3f B(red,green,blue);
	return B;
}
Eigen::Vector3f LightSource:: getXYZvector(){

	Eigen::Vector3f xyz(x,y,z);
	return xyz;
}

string LightSource:: toString(){
	return " X Y Z: " +to_string(x) + " "+to_string(y) + " "+to_string(z) +  " "+to_string(w) +
			"\n RGB: "+ to_string(red) + " "+ to_string(green)  + " "+ to_string(blue);

}

LightSource::~LightSource() {
	// TODO Auto-generated destructor stub
}

