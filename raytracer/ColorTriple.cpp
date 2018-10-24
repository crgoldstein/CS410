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
	red = CapColor(r) * 255;
	green =  CapColor(g)* 255;
	blue =  CapColor(b)* 255;
}


float ColorTriple::CapColor(float color){

	if(color < 0){
		return 0;
	}
	else if (color >1 ){
		return 1;
	}
	else{
		return color;
	}

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

