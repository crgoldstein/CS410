/*
 * CameraModel.h
 *
 *  Created on: Oct 6, 2018
 *      Author: clairegoldstein
 */

#ifndef CAMERAMODEL_H_
#define CAMERAMODEL_H_



#include "AmbientLight.h"
#include "LightSource.h"

#include <vector>
#include <Eigen/Dense>
#include <string>



using namespace std;

class CameraModel {

public:
	CameraModel();
	CameraModel(vector<string> &Driver, vector<LightSource> &LightS,AmbientLight &Ambient, vector<string> &Objs);
	virtual ~CameraModel();
	void test();
	void Run();


//private:

	Eigen::Vector3f pixelPt(int i, int j);
	float* RayTriangleInterection(Eigen::Vector3f &L, Eigen::Vector3f &D, Eigen::Vector3f &A, Eigen::Vector3f &B ,Eigen::Vector3f &C);

// Class Variables

	float EyeV[3];
	float LookV[3];
	float UpV[3];

	float Uv[3];// x
	float Vv[3];// y
	float Wv[3];// z


	//distance from the focal point to the image plane (near clipping plane)
	float near;

	//indicate the minimum and maximum extend of the bounded image
	//rectangle on the infinite image plane in the camera horizontal and vertical directions respectively.
	float left,right,top,bottom;

	//the resolution values separately indicate the pixel sampling resolution across the horizontal and vertical dimensions of the bounded rectangle.
	float width, height;

	vector<LightSource> LightSources;
	AmbientLight AmbientLight;
	vector<string> OBJs;
};

#endif /* CAMERAMODEL_H_ */
