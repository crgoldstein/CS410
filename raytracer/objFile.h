/*
 * objFile.h
 *
 *  Created on: Sep 10, 2018
 *      Author: clairegoldstein
 */

#ifndef OBJFILE_H_
#define OBJFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include "Face.h"
#include "point.h"
#include "Materials.h"

using namespace std;

class objFile {

public:
	objFile(const string DriverFile);
	objFile();
	virtual ~objFile();
	vector<Face> Faces;     // List of faces
	vector<point> Vertiecs; // List of faces
	bool smooth;
	string toString();

private:
	string ReadOBJ(const string file);
	Eigen::MatrixXd getVpoints();
	void setVpoints(Eigen::MatrixXd &points) ;
	void MakeFaces(string &MaterialString);
	void MakeVertiecsFromV();

	string DriverName;
	string OBJName;
	vector<string> File;
	vector<string> v;
	vector<string> f;


};

#endif /* OBJFILE_H_ */
