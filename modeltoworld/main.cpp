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

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#include <cstdlib>
#include "Transforms.h"
#include "objFile.h"
#include <unordered_map>
#include <sys/stat.h>

using namespace std;

int Usage(string arg0, string error){
  cout << "Usage: Input of:  " << arg0 << " Invaild " << endl;
  cout << "ERROR " <<  error << endl;
  return -1;
}


string newDIR(string driver){

	char cCurrentPath[FILENAME_MAX];
		 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		     {
		     return "";
		     }

		string Driver = string(driver);
		Driver =Driver.substr(0,Driver.length()-4);
		string FinalPath= ((string)cCurrentPath)+"/"+Driver ;

		//if ( exists(FinalPath)){}??  system


		struct stat statbuf;
		int isDir = 0;
		if (stat(FinalPath.c_str(), &statbuf) != -1) {
		   if (S_ISDIR(statbuf.st_mode)) {
		      isDir = 1;
		   }
		   //cout<< " DIRECTORY ALREADY THERE"<<endl;
		}
		else{
		string mkDIRfinal= "mkdir "+FinalPath;
			int n = mkDIRfinal.length();
		    char dir_path[n+1];
		    strcpy(dir_path, mkDIRfinal.c_str());
		    system(dir_path);
		}

	return FinalPath;

}


int TranslateOBJfiles(string file )
{
	vector <string> Driver;
	string Dir = newDIR(file);
	string oldFile;

 	//Read in File
	ifstream driver(file);// getting the file to match
	if (driver.fail()){
	    return Usage(file ,"ERROR in MAIN: in reading Driver File");

	}
	else
	{
		string line;
		while(getline(driver,line)){
			if (line.find("#") != std::string::npos) {
			    //Take out comment lines
			}
			else{
			Driver.push_back(line);
			}
		}

	}

	unordered_map <string, int> ObjCountTable;

	for (int i =  0; i < Driver.size(); i++)
	{
		vector<string> results;
		boost::split(results, Driver[i],boost::is_any_of(" "));

		vector<float> split;
		for (int j =  1; j< results.size() -1; j++)
		  {
			float a = strtof((results[j]).c_str(),0);
			split.push_back(a);
		  }

		 float rotate[3] = {split[0],split[1],split[2]};
		 float theta= split[3];
		 float scale = split[4];
		 float Transform[3]= {split[5],split[6],split[7]};


		 //Fixing Name of file
		 oldFile = results[9];
		 int ending = oldFile.length() -4 ;
		 string newNAME = oldFile.substr(0,ending) + "_mw0"+ to_string(ObjCountTable[oldFile]) + oldFile.substr(ending);
		 ObjCountTable[oldFile] = ObjCountTable[oldFile] +1;


	 // send to new Object
	 Transforms T(rotate, theta, scale,Transform);
	 objFile O(oldFile, newNAME, file);

	 Eigen::MatrixXf  RST = T.getRST();
	 Eigen::MatrixXf  Vpts = O.getVpoints();
	 Eigen::MatrixXf  RSTPoints = RST*Vpts.transpose();

	 O.setVpoints(&RSTPoints);
	 O.WriteNewOBJ(Dir);

	}

	return 0;
}



int main(int argc, char* argv[])
{

	if (argc != 2){// make sure there are the correct Number of Args
		 return Usage((string)argv[0]," ERROR in MAIN: Wrong number of arguments, FORMAT: modletoworld [driverfile].txt");
	}
	else
	{
		 return TranslateOBJfiles((string)argv[1]);
	}


	return 0;
}

