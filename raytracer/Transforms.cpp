/*
 * Transforms.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: Claire Goldstein
 */

#include "Transforms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <math.h>

using namespace std;


Transforms::Transforms( double rotateP[],  double theta,   double scale,  double translate[] ){
	RotateV=rotateP;
	ThetaV =theta;
	ScaleV = scale;
	TranslateV = translate;


}

Transforms::Transforms() {
	// TODO Auto-generated constructor stub
	//cout<<" hello from Transforms"<<endl;

}

Transforms::~Transforms() {
	// TODO Auto-generated destructor stub
}

Eigen::MatrixXd Transforms::getRotate(const double vector[], const double theta){
	//Axis Angle Rotation
		Eigen::Vector3d Wv(vector[0],vector[1],vector[2]);
		Eigen::Vector3d Mv(0,0,0);
		Eigen::Vector3d Uv(0,0,0);
		Eigen::Vector3d Vv(0,0,0);

		Wv = Wv.normalized();//.normalized()  Returns an expression of the quotient of *this by its own norm.

		//Need 2 other unit length vectors mutually orthongonal to W.
			//1. find a vector M that is not parallel to W.
			Mv <<abs(Wv(0)) , abs(Wv(1)), abs(Wv(2));

			double MinWv = Wv[0];
				for(int i =1 ; i<3; i++){
					if(Wv[i] < MinWv)
						MinWv=Wv[i];
				}

			int index=0;
				for(int i =0; i<3; i++){
				   if (Mv[i] == MinWv){
					  index =i ;
				   }
				}

			Mv[index]=1;

		//Second, now that the top and bottom row of our rotation matrix is defined,
			//the middle row is essentially define since it must be mutually orthongonal to the U and W vectors.

		    Uv=Wv.cross(Mv);//
			Uv=Uv.normalized();
			Vv= Wv.cross(Uv);// why dont you normaize Vv becouse Wv and Uv orthgonal and there for they produce unit leng things

			Eigen::MatrixXd m=Eigen::MatrixXd::Identity(4, 4);
				m(0,0) = Uv(0,0);m(0,1) = Uv(1,0);m(0,2) = Uv(2,0);
				m(1,0) = Vv(0,0);m(1,1) = Vv(1,0);m(1,2) = Vv(2,0);
				m(2,0) = Wv(0,0);m(2,1) = Wv(1,0);m(2,2) = Wv(2,0);

			Eigen::MatrixXd mT(3, 3);
			mT = m.transpose().eval();


//Rotate by theta about the xz-axis
		double radian =	(theta /180.0) * M_PI ;
		double ca = cos(radian);
		double sa = sin(radian);

		Eigen::MatrixXd z =Eigen::MatrixXd::Identity(4, 4);
			//if axis is Z:
				z(0,0)= ca;
				z(0,1)= -sa;
				z(1,0)= sa;
				z(1,1)= ca;


//Putting two Parts Together
		Eigen::MatrixXd Final(4,4);
		Final = mT * z * m;

		/*Checks for orthongonality
				cout<< "Mv \n"<< Mv<<endl;

				cout<<" Uv: \n"<< Uv<<endl;
				cout<<" Vv: \n"<< Vv<<endl;
				cout<<" Wv: \n"<< Wv<<endl;

				cout<<" m: \n"<< m<<endl;
				cout<<" mT: \n"<< mT<<endl;
				cout<<" m*mT: \n"<< m*mT<<endl;//Should be IDmaxtrix


				cout<<" z \n"<<z<<endl;

				cout<<"Final mT*z*m \n"<<Final<<endl;
				*/

	    return Final;
}

Eigen::MatrixXd Transforms::getScale(const double scale){

	Eigen::MatrixXd M =Eigen::MatrixXd::Identity(4, 4);
		M(0,0)=scale;
		M(1,1)=scale;
		M(2,2)=scale;

	    return M;
}


Eigen::MatrixXd Transforms::getTranslate( const double vector[]){
	Eigen::Vector3d Wv(vector[0],vector[1],vector[2]);

	Eigen::MatrixXd M = Eigen::MatrixXd::Identity(4, 4);
	M(0,3)= vector[0];
	M(1,3)= vector[1];
	M(2,3)= vector[2];

    return M;
}

Eigen::MatrixXd Transforms::getRST(){

    Eigen::MatrixXd RotateM = getRotate(RotateV,ThetaV);
    Eigen::MatrixXd ScaleM = getScale(ScaleV);
    Eigen::MatrixXd TranslateM = getTranslate(TranslateV);

    Eigen::MatrixXd M= TranslateM*ScaleM*RotateM ;

    return M;

}
