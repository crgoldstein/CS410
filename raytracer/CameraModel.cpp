/*
 * CameraModel.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: clairegoldstein
 */

#include "CameraModel.h"


#include <iostream>
#include <Eigen/Geometry>

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

#include <math.h>

using namespace std;

CameraModel::CameraModel() {}

CameraModel::CameraModel(vector<string> &Driver, vector<LightSource> &LightS,
						AmbientLight &ambient, vector<objFile> &Objs , vector<Sphere> &Sphs){
LightSourcesList = LightS;
	Ambient = ambient;
	OBJs = Objs;
	SPHs =Sphs;

		for (int i =  0; i < Driver.size(); i++)
				   {
printf("driver at i %s\n ",Driver[i].c_str());
					vector<string> line;
					boost::split(line, Driver[i] ,boost::is_any_of(" "));

					if (line.size() ==4){

							double a = stof((line[1]).c_str(),0);
							double b = stof((line[2]).c_str(),0);
							double c = stof((line[3]).c_str(),0);
							point X(a, b, c);
							if (line[0].compare("eye") == 0){
								 EyeV=X;
							}
							else if(line[0].compare("look") == 0){
								LookV=X;
							}
							else if(line[0].compare("up")==0){
								UpV=X;
							}

					}
					else if(line[0].compare("d")==0)
					{
						near = - strtof((line[1]).c_str(),0);
						//from the eye in the z direction to the near clippping plane

					}
					else if(line[0].compare("bounds")==0)
					{    //left, bottom, right, top
						left = strtof((line[1]).c_str(),0);
						bottom = strtof((line[2]).c_str(),0);
						right = strtof((line[3]).c_str(),0);
						top = strtof((line[3]).c_str(),0);

					}
					else if(line[0].compare("res")==0)
					{
						width = stoi(line[1]);
						height = stoi(line[2]);

					}
					else if (line[0].compare("recursionLevel")==0){
						recursionLevel = stoi(line[1]);
					}
				}// end of driver for loop

				Eigen::Vector3d wv(0,0,0);
				Eigen::Vector3d uv(0,0,0);
				Eigen::Vector3d vv(0,0,0);

				wv << EyeV.getVector() - LookV.getVector();;
				wv = wv.normalized();
				uv = UpV.getVector().cross(wv);
				uv = uv.normalized();
				vv = wv.cross(uv);

				Wv = point(wv(0),wv(1),wv(2));
				Uv = point(uv(0),uv(1),uv(2));
				Vv = point(vv(0),vv(1),vv(2));

}

Eigen::Vector3d CameraModel :: pixelPt(const int i, const int j){
	//if( )
	//printf(" pixelPt (%d, %d)\n",i,j);
    double px = (double)i/(width-1)*(right-left)+left;

    double py = (double)j/(height-1)*(bottom-top)+top;

    return EyeV.getVector()
			+ (near * Wv.getVector())
			+ (px * Uv.getVector())
			+ (py * Vv.getVector());;

}

void CameraModel:: RAY_CAST(Ray &ray, Eigen::Vector3d &Refatt, double *accumm, int depth){
	Eigen::Vector3d color;
	//printf("HIT something Recrisive depth %d > accumm is [ %f , %f , %f] \n",depth,accumm[0],accumm[1],accumm[2]);

	if (HitsSomething(ray)){

		if (ray.minTface < ray.minTsphere){ //Triangle is Closer
				Eigen::Vector3d pnt(ray.pointL + ray.minTface * ray.Direction.normalized());

				if (ray.Direction.normalized().dot(ray.closestFace.normal) > 0){// normal is pointing to the inside of the object
					ray.closestFace.setNormal(-ray.closestFace.normal);// Flip the normal;
				}

				color = COLOR_PIXEL(ray, ray.closestFace.normal, ray.closestFace.Material, pnt);
				accumm[0] += color(0) * Refatt(0) ;//red
				accumm[1] += color(1) * Refatt(1) ;//green
				accumm[2] += color(2) * Refatt(2) ;//blue

				//Recrisive
					if (depth > 0){
						Eigen::MatrixXd Kr = Eigen::MatrixXd::Identity(3, 3);
						Kr(0,0)=ray.closestFace.Material.KrRed;
						Kr(1,1)=ray.closestFace.Material.KrGreen;
						Kr(2,2)=ray.closestFace.Material.KrBlue;

						Refatt =  Kr * Refatt;

						Eigen::Vector3d  NewDir = -1 * ray.Direction;
						Eigen::Vector3d refR = ((2 * ray.closestFace.normal.dot(NewDir)) * ray.closestFace.normal) - NewDir ;
						refR= refR.normalized();
						Ray newRay(pnt , refR);

						RAY_CAST(newRay , Refatt, accumm, depth-1) ;
					   }
					else{
						return ;
					}
			}
			else{//Sphere is closer

				Eigen::Vector3d pnt(ray.pointL + ray.minTsphere * ray.Direction.normalized());
				Eigen::Vector3d r(ray.ClosestSphere.Center.getVector());
				Eigen::Vector3d SphereNormal(pnt - r); SphereNormal = SphereNormal.normalized();

				if (ray.Direction.normalized().dot(SphereNormal) > 0){// normal is pointing to the inside of the object
					SphereNormal =  - SphereNormal; // Flip the normal
				}

				color = COLOR_PIXEL(ray, SphereNormal, ray.ClosestSphere.Material, pnt);
				accumm[0] += color(0) * Refatt(0) ;//red
				accumm[1] += color(1) * Refatt(1) ;//green
				accumm[2] += color(2) * Refatt(2) ;//blue


				//Recrisive
					if (depth > 0){

							Eigen::MatrixXd Kr = Eigen::MatrixXd::Identity(3, 3);
							Kr(0,0) = ray.ClosestSphere.Material.KrRed;
							Kr(1,1) = ray.ClosestSphere.Material.KrGreen;
							Kr(2,2) = ray.ClosestSphere.Material.KrBlue;
							Refatt =  Kr * Refatt;

							Eigen::Vector3d DirInverse = -1 * ray.Direction;
							Eigen::Vector3d refR = (2 * SphereNormal.dot(DirInverse) * SphereNormal) - DirInverse ;
							refR = refR.normalized().eval();
							Ray newRay(pnt , refR);

							RAY_CAST(newRay ,Refatt, accumm, depth-1);
							return;

					}
					else{
						return ;
					}

			}
	}
    else{// YOU DONT NOT HIT ANYTHING
    	if(depth == 0){
    		 ColorTriple background =ColorTriple();
    		 accumm[0] += (double) background.getRed() * Refatt(0) ;
    		 accumm[1] += (double) background.getGreen() * Refatt(1) ;//green
    		 accumm[2] += (double) background.getBlue() * Refatt(2) ;//blue

    	}
    	return;
	}


}

bool CameraModel::HitsSomething(Ray &ray){
	bool HIT = false;

	for (Sphere S : SPHs){
			   if ( ray.RaySphereInterection(S) > 0){// checking if the ray actually hits the Sphere
				   HIT= true;
		   		}
			}

	 for(objFile object : OBJs){
			for(Face face : object.Faces ){
					if (ray.RayTriangleInterection(face) > 0){// checking if the ray actually hits the face
						HIT = true;
					}
			}
	 }

	return HIT;
}

Eigen::Vector3d CameraModel:: COLOR_PIXEL(Ray &ray, Eigen::Vector3d &Normal, Materials &Mat, Eigen::Vector3d &pnt ){

	Eigen::MatrixXd Ka = Eigen::MatrixXd::Identity(3, 3); Ka(0,0)=Mat.KaRed; Ka(1,1)=Mat.KaGreen; Ka(2,2)=Mat.KaBlue;
	Eigen::MatrixXd Kd = Eigen::MatrixXd::Identity(3, 3); Kd(0,0)=Mat.KdRed; Kd(1,1)=Mat.KdGreen; Kd(2,2)=Mat.KdBlue;
	Eigen::MatrixXd Ks = Eigen::MatrixXd::Identity(3, 3); Ks(0,0)=Mat.KsRed; Ks(1,1)=Mat.KsGreen; Ks(2,2)=Mat.KsBlue;

	Eigen::Vector3d Illumination(0,0,0) ;
//I= AmbientLight + SUM( Diffuss Light + Specular Light)

//AmbientLight: Ka * Brightness of AmbientLight
	Illumination = Ka * Ambient.getVector();//cout<<"Ambient lighting "<< Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<" "<<endl;

	for(int i=0; i <LightSourcesList.size(); i++ ){
		LightSource L(LightSourcesList[i]);

		Ray shadow(pnt, L.getXYZvector());
		bool hit = HitsSomething(shadow);

		if (!hit){//If there is NOT something in the way from point to light COLOR
					   Eigen::Vector3d lightS(L.getXYZvector() - pnt); lightS = lightS.normalized();

					   if(lightS.dot(Normal) > 0 ){// the light is NOT on the back side of the object
						   	 //Diffuse :  kd * brighness of light scorce  * (L dot normal)
							Illumination +=  Kd * L.getBrightnessVector() * lightS.dot(Normal); //cout<<"Diffuse lighting "<<Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<" "<<endl;

							//Specular   : ks * brighness of light scorce * (2(N dot L )* N -L dot V )^phong
							Eigen::Vector3d toC  = ray.pointL - pnt ; toC = toC.normalized();
							Eigen::Vector3d spR  = (2 * lightS.dot(Normal) * Normal) - lightS;
							double CdR  = toC.dot(spR);
							if (CdR > 0.0){
								Illumination +=  (Ks * L.getBrightnessVector()) * (pow(CdR ,Mat.phong)); //cout<<"AFTER Specular  "<<Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<endl;
								}
					   }
		   		}
		}//end of forEach

    // write the resulting RGB into the pixel
	return Illumination;

}

vector<vector<ColorTriple> > CameraModel:: Run(){
printf("Run\n height %d width %d \n",height, width);
	vector<vector<ColorTriple> > FileColor;

	Eigen::Vector3d pixel, Direction;

	for(int x =0; x < height ; x++){
		vector<ColorTriple> temp;
		for(int y=0; y < width; y++){// for each pixel in the image to be rendered
			       //fire a ray into the scene and determine the first( the smallest  t value) visible surface
							    // for each pixel hit into each face
								//printf("in run [%d,%d]  ",x ,y);
								pixel = pixelPt(x,y);
								//printf("PIXEL %f %f %f \n ",pixel(0),pixel(1),pixel(2));
								Direction = pixel - EyeV.getVector(); //(pixel point)- eye

								//printf("Direction %f %f %f \n ",Direction(0),Direction(1),Direction(2));
								Ray r(pixel,Direction);
								//printf("Ray %s \n ",r.toString().c_str());
								Eigen::Vector3d Refatt(1,1,1);
								double accumm[] = {0,0,0};
								RAY_CAST(r, Refatt, accumm, recursionLevel);
								ColorTriple rgb(accumm[0],accumm[1],accumm[2]);
							    temp.push_back(rgb);

		}//end of ForLoop y
		FileColor.push_back(temp);
	}//end of ForLoop x

	return FileColor;

}

CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}

