/*
 * objFile.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: Claire Goldstein
 */

#include "objFile.h"
#include "Transforms.h"
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split


using namespace std;

objFile::objFile(const string Driver) {

		vector<string> results;
		boost::split(results, Driver,boost::is_any_of(" "));
		//  0	1	2	3 	4  5  6  7    8      9
		//model 1.0 1.0 0.0 30 2 0.0 0.0 -15.0 cube_centered.obj

		double rotate[3] = {strtof((results[1]).c_str(),0), strtof((results[2]).c_str(),0) ,strtof((results[3]).c_str(),0)};
		double theta= strtof((results[4]).c_str(),0);
		double scale = strtof((results[5]).c_str(),0);
		double Transform[3]= {strtof((results[6]).c_str(),0), strtof((results[7]).c_str(),0) ,strtof((results[8]).c_str(),0)};

		// send to new Object
		Transforms T(rotate, theta, scale, Transform);

		//Reading OBJ file
		string Material = ReadOBJ(results[9]);
		//Rotating and Updating the V poitns
		Eigen::MatrixXd  RST (T.getRST());
		Eigen::MatrixXd  Vpts(getVpoints());
	 	Eigen::MatrixXd  RSTPoints(RST*Vpts.transpose());
	 	setVpoints(RSTPoints);
	 	//Make Face Objects that have points ABC and Materials
	 	MakeFaces(Material);

}

string objFile:: ReadOBJ(const string fileName){
	string location = fileName;
	ifstream file(location);// getting the file to match

		if (! file.is_open())
		{
				cout <<"Error opening .OBJ file" <<endl;
				cout<<"Failed at "<<  location <<endl;
				exit (1);
		}
		else
		{
		       string line;
			   while(getline(file,line)){
			 		 File.push_back(line);
			 			}
		}

			 	string Material ="";
			 	for(int i=0; i<File.size(); i++)
			 	{
			 			vector<string> objLine;
			 			boost::split(objLine, File[i],boost::is_any_of(" "));

			 			if(objLine[0].compare("v") == 0)
			 					v.push_back(File[i]);

			 			if(objLine[0].compare("f") == 0)
			 					f.push_back(File[i]);

			 			if (objLine[0].compare("mtllib")==0)
			 				Material = objLine[1];

			 	}
	return Material;

}

Eigen::MatrixXd objFile:: getVpoints(){

	Eigen::MatrixXd m (v.size(),4);
			for(int i=0; i<v.size(); i++)
			{
				vector<string> results;
				boost::split(results, v[i],boost::is_any_of(" "));

				m(i,0)=strtof((results[1]).c_str(),0);
				m(i,1)=strtof((results[2]).c_str(),0);
				m(i,2)=  strtof((results[3]).c_str(),0);
				m(i,3)=1;
			}

	return m;
}

void objFile::setVpoints(Eigen::MatrixXd &points) {
	//Eigen::MatrixXd newV = *points;
	for(int i =0; i<v.size(); i++){
		string x = to_string(points(0,i));
		string y = to_string(points(1,i));
		string z = to_string(points(2,i));
	    v[i] ="v "+ x +  " " +y + " " +z;
	}
}

void objFile:: MakeFaces(string &MaterialString){
	Materials M(MaterialString);
	point Apoint; point Bpoint; point Cpoint;
	for(int i =0; i< f.size(); i++){
        //0   1    2    3
		//f 2//1 4//1 1//1

		vector<string> results;
		boost::split(results, f[i],boost::is_any_of(" "));

		    vector<string> SlashA;
			boost::split(SlashA, results[1] ,boost::is_any_of("/"));
			int A = stoi(SlashA[0]);// string to int

			vector<string> SlashB;
			boost::split(SlashB, results[2],boost::is_any_of("/"));
			int B = stoi(SlashB[0]);

			vector<string> SlashC;
			boost::split(SlashC, results[3],boost::is_any_of("/"));
			int C = stoi(SlashC[0]);

		//Make points
		Apoint = MakePointFromV(A);
		Bpoint = MakePointFromV(B);
		Cpoint = MakePointFromV(C);
		Face F(Apoint, Bpoint, Cpoint, M);


		Faces.push_back(F);

	}
}

point objFile:: MakePointFromV(int Index){
	Index= Index - 1;
	vector<string> results;
	boost::split(results, v[Index],boost::is_any_of(" "));

	double a = strtof((results[1]).c_str(),0);
	double b = strtof((results[2]).c_str(),0);
	double c = strtof((results[3]).c_str(),0);

    point newPoint(a,b,c);
    return newPoint;

}


objFile::~objFile() {
	// TODO Auto-generated destructor stub
}
