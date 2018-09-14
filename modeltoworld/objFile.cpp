/*
 * objFile.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: clairegoldstein
 */

#include "objFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::spli



using namespace std;

objFile::objFile(string OBJfile, string DriverFile ) {
	// TODO Auto-generated constructor stub
	DriverName=DriverFile;
	OBJName=OBJfile;
	ifstream file("models/"+OBJfile);// getting the file to match

	if (file.fail()){
			   // return error
	}
	else
	{
			string line;
			while(getline(file,line)){
					File.push_back(line);
			}
	}
	for(int i=0; i<File.size(); i++){
			vector<string> results;
			boost::split(results, File[i],boost::is_any_of(" "));

			if(results[0].compare("#") == 0){
				Comments.push_back(File[i]);
			}
			if(results[0].compare("v") == 0){
					v.push_back(File[i]);
			}
			if(results[0].compare("vn") == 0){
					vn.push_back(File[i]);
			}
			if(results[0].compare("s") == 0){
					s.push_back(File[i]);
			}
			if(results[0].compare("f") == 0){
					f.push_back(File[i]);
			}
	}

}

objFile::~objFile() {
	// TODO Auto-generated destructor stub
}


void objFile::WriteNewOBJ(){
	vector<string> NewFile;

	vector< vector<string> > Parts;
	Parts.push_back(Comments);
	Parts.push_back(v);
	Parts.push_back(f);

	for(int i=0; i<Parts.size(); i++){
		for(int j=0; j<Parts[i].size(); j++){// Comments , v ,vn ,s, f
			NewFile.push_back(Parts[i][j]);
		}
	}

	ofstream output_file("/Users/clairegoldstein/Desktop/example.txt");
	ostream_iterator<string> output_iterator(output_file, "\n");
    copy(NewFile.begin(), NewFile.end(), output_iterator);


}



Eigen::MatrixXf objFile::getVpoints(){

	Eigen::MatrixXf m (v.size(),4);
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

void objFile::setVpoints(Eigen::MatrixXf* points){
	Eigen::MatrixXf newV = *points;

	for(int i =0; i<v.size(); i++){
		string x = to_string(newV(0,i));
		string y = to_string(newV(1,i));
		string z = to_string(newV(2,i));
	    v[i] ="v "+ x +  " " +y + " " +z;
	}

	cout<<"New Vpts in setVpoints"<<endl;

	for(int i =0; i<v.size(); i++){
		cout<<v[i]<<endl;
	}




}
