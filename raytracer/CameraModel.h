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
#include "objFile.h"
#include "point.h"
#include "Ray.h"
#include "ColorTriple.h"

#include <vector>
#include <Eigen/Dense>
#include <string>



using namespace std;

class CameraModel {

public:
	CameraModel();
	CameraModel(vector<string> &Driver, vector<LightSource> &LightS,AmbientLight &ambient, vector<objFile> &Objs);
	virtual ~CameraModel();
	void testP2();
	vector<vector<ColorTriple> > Run();


private:
	Eigen::Vector3f pixelPt(const int i,const int j);
	float RayTriangleInterection(Eigen::Vector3f &L, Eigen::Vector3f &D, Face &f);//Eigen::Vector3f &A, Eigen::Vector3f &B ,Eigen::Vector3f &C);

	ColorTriple  RAY_CAST(const int i,const int j);//why can't i pass by referance
	ColorTriple  COLOR_PIXEL (Ray &ray, Face &face);

// Class Variables
	point EyeV;
	point LookV;
	point UpV;

	point Uv;// x
	point Vv;// y
	point Wv;// z

	//distance from the focal point to the image plane (near clipping plane)
	float near;
	//indicate the minimum and maximum extend of the bounded image
	//rectangle on the infinite image plane in the camera horizontal and vertical directions respectively.
	float left,right,top,bottom;
	//the resolution values separately indicate the pixel sampling resolution across the horizontal and vertical dimensions of the bounded rectangle.
	int width, height;

	vector<LightSource> LightSourcesList;
	AmbientLight Ambient;
	vector<objFile> OBJs;
};

#endif /* CAMERAMODEL_H_ */
