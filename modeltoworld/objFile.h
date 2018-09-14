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

using namespace std;
class objFile {

public:
	objFile(std::string OBJfile, std::string DriverFile);
	objFile();
	virtual ~objFile();

	void WriteNewOBJ( );

	Eigen::MatrixXf getVpoints();
	void setVpoints(Eigen::MatrixXf* points);


private:
	string DriverName;
	string OBJName;
	vector<string> File;

	vector<string> Comments;
	vector<string> v;
	vector<string> vn;
	vector<string> s;
	vector<string> f;




};

#endif /* OBJFILE_H_ */
