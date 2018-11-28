/*
 * Sphere.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: claire goldstein
 */

#include "Sphere.h"

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <vector>
#include "Ray.h"

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
				for (int i = 5; i<line.size(); i++){
					Mats.push_back(strtof(line[i].c_str(),0));
				}

				Material = Materials(Mats);
}

string Sphere:: toString(){
	return "Center point "+ Center.toString()
			+"\n Radius "+ to_string(radius)
			+"\n Material "+ Material.toString();
}

Ray Sphere:: refract_exit(Eigen::Vector3d W,Eigen::Vector3d pt, double eta_inside){
	Eigen::Vector3d  T1 = refract_tray(W, pt, (pt - Center.getVector()).normalized(), 1.0, eta_inside);

	// cout<<"W "<< W(0) <<" "<<W(1) <<" "<<W(2) <<endl;
	// cout<<"pt "<<pt(0) <<" "<<pt(1) <<" "<<pt(2) <<endl;
	// cout<<"T1 "<<T1(0) <<" "<<T1(1) <<" "<<T1(2) <<endl;

	if((T1(0) + T1(1) + T1(2) ) == 0.0 && T1(0)== 0 &&  T1(1) == 0 && T1(2) == 0 ){
				return Ray();// Check for Point and Direction == 0
	}
	else{
				Eigen::Vector3d Exit = pt + 2 *( (Center.getVector() - pt).dot(T1) ) * T1;
				Eigen::Vector3d Nin = (Center.getVector() - Exit).normalized();
				Eigen::Vector3d T2 = refract_tray(-T1, Exit, Nin, eta_inside,1.0);
 				Ray refR(Exit, T2);
				//cout<<" exit Ray: refR "<< refR.toString()<<endl;
				return refR;
	}

}

Eigen::Vector3d  Sphere::refract_tray(Eigen::Vector3d W , Eigen::Vector3d pt, Eigen::Vector3d Normal,
	 													 double eta1, double eta2){

	 //Snell's Law
	 double etar = eta1 / eta2;
	 double a = - etar;
	 double wn = W.dot(Normal);

	 double RadSq = pow(etar,2) *  (pow(wn,2) - 1) + 1 ;
	 if (RadSq < 0.0)
	 			return Eigen::Vector3d (0,0,0);
	 else{
			 double b = (etar * wn) - sqrt(RadSq);
			 Eigen::Vector3d T = a * W + b * Normal;
			 return T ;
	 }

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}
