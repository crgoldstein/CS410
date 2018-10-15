/*
 * PPMFile.h
 *
 *  Created on: Oct 10, 2018
 *      Author: clairegoldstein
 */

#ifndef PPMFILE_H_
#define PPMFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ColorTriple.h"

using namespace std;

class PPMFile {
public:
	PPMFile();
	PPMFile(const string FileName);
	void write(vector<vector<ColorTriple> > &FileColor);
	virtual ~PPMFile();

	string filename;
};

#endif /* PPMFILE_H_ */
