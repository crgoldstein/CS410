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
#include <boost/algorithm/string/split.hpp> // Include for boost::spli
#include <Eigen/Dense>

#include "Transforms.h"
#include "objFile.h"

using namespace std;

int Usage(char* arg0, string error){
  cout << "Usage: Input of:  " << arg0 << " Invaild " << endl;
  cout << "ERROR " <<  error << endl;
  return -1;
}


int main(int argc, char* argv[])
{
	vector <string> Driver;
	cout <<" Hello from main.cpp again"<< endl;

	if (argc != 2){// make sure there are the correct Number of Args
		cout <<"Else "<< argc<< endl;
		 return Usage(argv[0]," ERROR in MAIN: Wrong number of arguments, FORMAT: modletoworld [driverfile].txt");

	}
	else
	{
	 	//Read in File
		ifstream driver(argv[1]);// getting the file to match


		if (driver.fail()){
		    Usage(argv[1],"ERROR in MAIN: in reading Driver File");
		    return -1;
		}
		else
		{
			string line;
			while(getline(driver,line)){
				Driver.push_back(line);
			}
		}

	}


	for (int i =  0; i < Driver.size(); i++)
	{
	 //model 0.0 1.0 0.0 30 3.0 10.0 0.0 10.0 cube.obj
	 string text = Driver[i];
	 cout<< text<<endl;
	 vector<string> results;

	 boost::split(results, text,boost::is_any_of(" "));

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
		 string file = results[9];

	 // send to new Object

	 Transforms T(rotate, theta, scale,Transform);
	 Eigen::MatrixXd  RST= T.getRST();
	 objFile O(file,argv[1]);
	 Eigen::MatrixXd  Vpts=  O.getVpoints();



	 cout<< "\n RST in Main \n" << RST<< endl;

	 cout<< "\n Vpts.transpose() in Main \n" << Vpts.transpose()<< endl;


	 Eigen::MatrixXd  final =RST*Vpts.transpose();
	 cout<< "\n RST*Vpts.transpose() in Main \n" << final<< endl;
	 O.setVpoints(&final);

	}



	return 0;
}

