/*
 * Ray.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#include "Ray.h"
#include "math.h"


Ray::Ray(){
		Pixel << 0,0,0;
		Direction  << 0,0,0;

		minTface=numeric_limits<float>::max();
		closestFace=Face();

		minTsphere =numeric_limits<float>::max();
		ClosestSphere = Sphere();


}

Ray::Ray(const Eigen::Vector3f &P, const Eigen::Vector3f &D) {
	Pixel = P;
	Direction = D;

	minTface =numeric_limits<float>::max();
	closestFace=Face();

	minTsphere = numeric_limits<float>::max();
	ClosestSphere = Sphere();

}

float Ray:: RayTriangleInterection(Face &f){//Eigen::Vector3f &A, Eigen::Vector3f &B ,Eigen::Vector3f &C){
	//Cramer's Rule.
		//This approach involves solving for the determinants of four matrices,
		//the original M matrix and then three derived by substituting Y into successive columns.
	  Eigen::Vector3f D = Direction;

			    			D=D.normalized().eval();
							Eigen::Vector3f A(f.A.getVector());
							Eigen::Vector3f B(f.B.getVector());
							Eigen::Vector3f C(f.C.getVector());


							Eigen::Vector3f AminusL(A-Pixel);
							Eigen::Matrix3f M;   M << (A-B)   ,(A-C),   D;
							M =M.transpose().eval();

			//BETA
							Eigen::Matrix3f M1; M1 << AminusL ,(A-C),   D;
							M1=M1.transpose().eval();
							float beta = M1.determinant()/ M.determinant();
								if (beta < 0.0)
									return -1.0;

			//GAMMA
							Eigen::Matrix3f M2; M2 << (A-B)   ,AminusL, D;
							M2=M2.transpose().eval();
							float gamma = M2.determinant()/ M.determinant();
								if (gamma < 0.0)
									return -1.0;
								if (beta +gamma >1.0)
									return -1.0;

			//T
							Eigen::Matrix3f M3; M3 << (A-B) ,(A-C),   AminusL;
							M3=M3.transpose().eval();
							float t = M3.determinant()/ M.determinant();
								if (t>0){

									if (t < minTface){ // checking if its the first visible surface aka the Smallest T value
										minTface = t;
										closestFace = f;
									}

									return t;
								}
								else{
									return -1.0;
								}


}

float Ray:: RaySphereInterection(Sphere &S){

	  	Eigen::Vector3f D = Direction; D=D.normalized().eval();
		Eigen::Vector3f Tv = (S.Center.getVector() - Pixel);
	    float v    = Tv.dot(D) ;
	    float csq  = Tv.dot(Tv) ;
	    float disc = pow(S.radius,2 ) - (csq - pow(v,2));

	    if (disc < 0)
	        return -1.0;
	    else {
	        float d  = sqrt(disc);
	        float t  = v - d;
	        if (t < minTface && t>0.00001){ // checking if its the first visible surface aka the Smallest T value
	        	minTsphere = t;
	        	ClosestSphere = S;
	        }
	        return t;
	    }
}

string Ray::toString(){
	return "Pixel  " + to_string(Pixel(0))+" "+to_string( Pixel(1))+" "+ to_string(Pixel(2))
			+ "\nDirection  " +to_string(Direction(0))+" " +to_string(Direction(1))+" " +to_string(Direction(2))+" "
			+"\n minTface"+ to_string(minTface)
			+"\n minTsphere"+ to_string(minTsphere);

}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

