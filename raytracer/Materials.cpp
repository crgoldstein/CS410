/*
 * Materials.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#include "Materials.h"
#include <vector>


#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split



Materials::Materials() {
	// TODO Auto-generated constructor stub
	this->KaRed= 0;
	this->KaGreen= 0;
	this->KaBlue= 0;
	this->KdRed= 0;
	this->KdGreen= 0;
	this->KdBlue= 0;
	this->KsRed= 0;
	this->KsGreen= 0;
	this->KsBlue= 0;
}


Materials::Materials(string fileName){
	string location = "drivers_models/"+fileName;
	ifstream file(location);// getting the file to match

	vector<string> File;

			if (! file.is_open())
			{
					cout << "Error opening materials  file" <<endl;
					cout<<"failed at "<<  location <<endl;
					exit (1);
			}
			else
			{
			       string line;
				   while(getline(file,line)){
				 		 File.push_back(line);
				 			}
			}

				for(int i=0; i<File.size(); i++)
				{
					vector<string> matLine;
					boost::split(matLine, File[i],boost::is_any_of(" "));

					if(matLine[0].compare("Ka") == 0){
						KaRed= strtof(matLine[1].c_str(),0);
						KaGreen= strtof(matLine[2].c_str(),0);
						KaBlue= strtof(matLine[3].c_str(),0);

					}
					if(matLine[0].compare("Kd") == 0){
						KdRed= strtof(matLine[1].c_str(),0);
						KdGreen= strtof(matLine[2].c_str(),0);
						KdBlue= strtof(matLine[3].c_str(),0);
					}
					if (matLine[0].compare("Ks")==0){
						KsRed= strtof(matLine[1].c_str(),0);
						KsGreen= strtof(matLine[2].c_str(),0);
						KsBlue= strtof(matLine[3].c_str(),0);
					}
				}


}


Eigen::Vector3f Materials::getKaVector(){

	Eigen::Vector3f vectorKA;
	vectorKA << KaRed, KaGreen, KaBlue ;
	return vectorKA;

}
Eigen::Vector3f Materials:: getKdVector(){

		Eigen::Vector3f vectorKd;
		vectorKd<< KdRed, KdGreen, KdBlue ;
		return vectorKd;

}
Eigen::Vector3f Materials:: getKsVector(){

			Eigen::Vector3f vectorKs;
			vectorKs<< KsRed, KsGreen, KsBlue ;
			return vectorKs;
}

string Materials::toString(){

	return "\n		Ka: "+ to_string(KaRed) + " "+ to_string(KaGreen) + " "+ to_string(KaBlue)
			+ "\n		Kd: "+ to_string(KdRed) + " "+ to_string(KdGreen) + " "+ to_string(KdBlue)
			+ "\n		Ks: "+ to_string(KsRed) + " "+ to_string(KsGreen) + " "+ to_string(KsBlue) ;
}

Materials::~Materials() {
	// TODO Auto-generated destructor stub
}

