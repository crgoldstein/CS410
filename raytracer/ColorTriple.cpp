/*
 * ColorTriple.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: clairegoldstein
 */

#include "ColorTriple.h"

ColorTriple::ColorTriple() {
	    //This is the background color
		red = 0;
		green = 0;
		blue = 0;

}

ColorTriple:: ColorTriple(const float r, const float g , const float b){
	red = r * 255;
	green =  g* 255;
	blue =  b* 255;
}

int ColorTriple:: getRed() {
		return red;
}
int ColorTriple:: getGreen(){
	return green;
}
int ColorTriple:: getBlue(){
		return blue;
}

string ColorTriple:: toString(){

	return  to_string(red)+ " "+ to_string(green) + " "+ to_string(blue) +" ";
}
ColorTriple::~ColorTriple() {
	// TODO Auto-generated destructor stub
}

