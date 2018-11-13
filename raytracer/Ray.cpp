/*
 * Ray.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: clairegoldstein
 */

#include "Ray.h"
#include "math.h"
#include <iostream>


Ray::Ray(){
	    pointL << 0,0,0;
		Direction  << 0,0,0;

		minTface=numeric_limits<double>::max();
		minGamma = numeric_limits<double>::max();
		minBeta = numeric_limits<double>::max();
		closestFace=Face();

		minTsphere =numeric_limits<double>::max();
		ClosestSphere = Sphere();


}

Ray::Ray(const Eigen::Vector3d &P, const Eigen::Vector3d &D) {
	pointL = P;
	Direction = D;


	minTface = numeric_limits<double>::max();
	minGamma = numeric_limits<double>::max();
	minBeta = numeric_limits<double>::max();
	closestFace=Face();

	minTsphere = numeric_limits<double>::max();
	ClosestSphere = Sphere();

}

double Ray:: RayTriangleInterection(Face &f){
	//Cramer's Rule.
		//This approach involves solving for the determinants of four matrices,
		//the original M matrix and then three derived by substituting Y into successive columns.
	  Eigen::Vector3d D = Direction;

			    			D=D.normalized().eval();
							Eigen::Vector3d A(f.A.getVector());
							Eigen::Vector3d B(f.B.getVector());
							Eigen::Vector3d C(f.C.getVector());


							Eigen::Vector3d AminusL(A - pointL);

							Eigen::Matrix3d M;   M << (A-B) ,(A-C),  D;
							M = M.transpose().eval();
							//printf("pointL %f %f %f\n",pointL(0),pointL(1),pointL(2));
							//printf("D %f %f %f \n",D(0),D(1),D(2));
			//BETA
							Eigen::Matrix3d M1; M1 << AminusL ,(A-C),   D;
							M1=M1.transpose().eval();
							double beta = M1.determinant()/ M.determinant();
							//printf("beta %f\n",beta);
								if (beta < 0.0)
									return -1.0;

			//GAMMA
							Eigen::Matrix3d M2; M2 << (A-B)   ,AminusL, D;
							M2=M2.transpose().eval();
							double gamma = M2.determinant()/ M.determinant();
							//printf("gamma %f\n",gamma);
								if (gamma < 0.0)
									return -1.0;
								if (beta +gamma >1.0)
									return -1.0;

			//T
							Eigen::Matrix3d M3; M3 << (A-B) ,(A-C), AminusL;
							M3=M3.transpose().eval();
							double t = M3.determinant()/ M.determinant();
							//printf("t %f\n",t);
							if (t>0.000001 && beta>=0 && gamma >= 0.0  && beta + gamma <= 1.0 && t < minTface){
									// checking if its the first visible surface aka the Smallest T value
									minTface = t;
									minGamma = gamma;
									minBeta = beta;
									closestFace = f;

									return t;
							}
							else{
									return -1.0;
							}


}

double Ray:: RaySphereInterection(Sphere &S){

	  	Eigen::Vector3d D = Direction; D=D.normalized().eval();
		  Eigen::Vector3d Tv = (S.Center.getVector() - pointL);
	    double v    = Tv.dot(D) ;
	    double csq  = Tv.dot(Tv) ;
	    double disc = pow(S.radius,2 ) - (csq - pow(v,2));

	    if (disc < 0)
	        return -1.0;
	    else {
	        double d  = sqrt(disc);
	        double t  = v - d;
	        if (t < minTsphere && t>0.00001){ // checking if its the first visible surface aka the Smallest T value
	        	minTsphere = t;
	        	ClosestSphere = S;
	        }
	        return t;
	    }
}

string Ray::toString(){
	return "pointL  " + to_string(pointL(0))+" "+to_string( pointL(1))+" "+ to_string(pointL(2))
			+ "\nDirection  " +to_string(Direction(0))+" " +to_string(Direction(1))+" " +to_string(Direction(2))+" ";
			//+"\n minTface"+ to_string(minTface)
			//+"\n minTsphere"+ to_string(minTsphere);

}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}
