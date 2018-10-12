/*
 * ColorTriple.h
 *
 *  Created on: Oct 10, 2018
 *      Author: clairegoldstein
 */

#ifndef COLORTRIPLE_H_
#define COLORTRIPLE_H_

#include <string>
#include <iostream>

using namespace std;

class ColorTriple {
public:
	ColorTriple();
	ColorTriple(float r, float g , float b);
	int getRed();
	int getGreen();
	int getBlue();
	virtual ~ColorTriple();
	string toString();

private:
	int red, green, blue;

};

#endif /* COLORTRIPLE_H_ */
