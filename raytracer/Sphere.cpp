/*
 * Sphere.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: clairegoldstein
 */

#include "Sphere.h"

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <vector>

using namespace std;

Sphere::Sphere() {
	Center = point();

	radius = 0;

	Material = Materials();

}

Sphere::Sphere(const string Driver) {
				vector<string> line;
				boost::split(line, Driver, boost::is_any_of(" "));
				//Point Center
			  double x = strtof(line[1].c_str(),0);
				double y = strtof(line[2].c_str(),0);
				double z = strtof(line[3].c_str(),0);

				Center = point( x ,y, z) ;
				radius = strtof(line[4].c_str(),0);

				//Materials
				vector<double> Mats;
				for (int i =5; i<line.size(); i++){
					Mats.push_back(strtof(line[i].c_str(),0));
				}

				Material = Materials(Mats);
}


string Sphere:: toString(){
	return "Center point "+ Center.toString()
			+"\n Radius "+ to_string(radius)
			+"\n Material "+ Material.toString();
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}
