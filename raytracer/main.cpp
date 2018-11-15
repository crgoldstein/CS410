/*
 * main.cpp
 *
 * Created on: Sep 4, 2018
 * Author: Claire Goldstein
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <Eigen/Dense>

#include <sys/stat.h>
#include <cstdlib>

#include "Transforms.h"
#include "objFile.h"
#include "CameraModel.h"
#include "AmbientLight.h"
#include "LightSource.h"
#include "PPMFile.h"
#include "Sphere.h"

using namespace std;

int Usage(string arg0, string error){
  cout << "Usage: Input of:  " << arg0 << " Invaild " << endl;
  cout << "ERROR " <<  error << endl;
  return -1;
}

int main(int argc, char* argv[])
{
	if (argc != 3){// make sure there are the correct Number of Args
		 return Usage((string)argv[0]," ERROR in MAIN: Wrong number of arguments, FORMAT: ./raytracer driver00.txt driver00.ppm");
	}
	else
	{
		PPMFile ppmFile(argv[2]);
		vector <string> model;
		vector <string> sphere;
		vector <string> cameraElements;
		vector <string> light;
		string ambient;

		//Read in File
			ifstream driver(argv[1]);// getting the file to match
			if (driver.fail()){
			    return Usage(argv[1] ,"ERROR in MAIN: in reading Driver File");
			}
			else// split up the parts of the driver file
			{
				string line;
				while(getline(driver,line)){

					if (line.find("#") != std::string::npos) {}

					else if (line.find("light") != std::string::npos )
						light.push_back(line);

					else if (line.find("ambient") != std::string::npos )
						ambient=line;

					else if (line.find("model") != std::string::npos )
						model.push_back(line);

					else if (line.find("sphere") != std::string::npos )
						sphere.push_back(line);
					else
						cameraElements.push_back(line);
				}
			}

//Set up lighting
		AmbientLight backgorundLight(ambient);

		vector<LightSource> Lighting;
		for(string L : light){
			Lighting.push_back(LightSource (L));
		}

		vector<Sphere> sph;
		for (string S: sphere){
			sph.push_back(Sphere (S));
		}

		vector<objFile> OBJs;
    for(int i =0; i<model.size();i++){
			 OBJs.push_back(objFile (i, model[i]));
		}

		 // Set Up Camera model
		 CameraModel CAMERA(cameraElements,Lighting,backgorundLight,OBJs,sph);
//
		 vector<vector<ColorTriple> >  FileColor = CAMERA.Run();
		 ppmFile.write(FileColor);
		 return 0;
	}


	return 0;
}
