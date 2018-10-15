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
	vector<Face> Faces;

private:
	string ReadOBJ(const string file);
	Eigen::MatrixXf getVpoints();
	void setVpoints(Eigen::MatrixXf& points) ;
	void MakeFaces(string &MaterialString);
	point MakePointFromV(int Index);

	string DriverName;
	string OBJName;
	vector<string> File;

	vector<string> v;
	vector<string> f;


};

#endif /* OBJFILE_H_ */
