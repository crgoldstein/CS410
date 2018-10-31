/*
 * ColorTriple.h
 *  Created on: Oct 10, 2018
 *      Author: clairegoldstein
 */
#ifndef COLORTRIPLE_H_
#define COLORTRIPLE_H_
#include <string>

using namespace std;

class ColorTriple {
public:
	ColorTriple();
	ColorTriple(const double r,  const double g , const double b);
	int getRed() ;
	int getGreen() ;
	int getBlue() ;
	double CapColor(double color);

	virtual ~ColorTriple();
	string toString();

private:
	int red, green, blue;

};

#endif /* COLORTRIPLE_H_ */
