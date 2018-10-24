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
					vector<string> line;
					boost::split(line, Driver[i] ,boost::is_any_of(" "));

					if (line.size() ==4){

							float a = stof((line[1]).c_str(),0);
							float b = stof((line[2]).c_str(),0);
							float c = stof((line[3]).c_str(),0);
							point X(a, b, c);
							if (line[0].compare("eye")==0){
								 EyeV=X;
							}
							else if(line[0].compare("look")==0){
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
				}// end of driver for loop



				Eigen::Vector3f wv(0,0,0);
				Eigen::Vector3f uv(0,0,0);
				Eigen::Vector3f vv(0,0,0);

				wv << EyeV.getVector() - LookV.getVector();;
				wv = wv.normalized();
				uv = UpV.getVector().cross(wv);
				uv = uv.normalized();
				vv = wv.cross(uv);

				Wv = point(wv(0),wv(1),wv(2));
				Uv = point(uv(0),uv(1),uv(2));
				Vv = point(vv(0),vv(1),vv(2));

}

Eigen::Vector3f CameraModel:: pixelPt(const int i, const int j){
    float px = (float)i/(width-1)*(right-left)+left;

    float py = (float)j/(height-1)*(bottom-top)+top;

    return EyeV.getVector()
			+ (near * Wv.getVector())
			+ (px * Uv.getVector())
			+ (py * Vv.getVector());;

}

ColorTriple CameraModel:: RAY_CAST(Ray &ray){
	  if (HitsSomething(ray)){
			if (ray.minTface < ray.minTsphere){//Triangle is Closer
				cout<<"RAY_CAST :Hits Triangle  "<<endl;
				Eigen::Vector3f pnt(ray.Pixel + ray.minTface * ray.Direction.normalized());

				if (ray.Direction.normalized().dot(ray.closestFace.normal) > 0){// normal is pointing to the inside of the object
					ray.closestFace.setNormal(-ray.closestFace.normal);// Flip the normal;
				}
				return COLOR_PIXEL(ray, ray.closestFace.normal, ray.closestFace.Material, pnt);

			}
			else{//Sphere is closer
				cout<<"RAY_CAST :Hits Sphere  "<<endl;
				Eigen::Vector3f pnt(ray.Pixel + ray.minTsphere *ray.Direction.normalized());
				Eigen::Vector3f SphereNormal(pnt - ray.ClosestSphere.Center.getVector());//snrm = ptos - sph['c']; snrm = snrm / snrm.norm() # serface Normal
				SphereNormal = SphereNormal.normalized();

				if (ray.Direction.normalized().dot(SphereNormal) > 0){// normal is pointing to the inside of the object
					SphereNormal =  -SphereNormal; // Flip the normal;
				}

				return COLOR_PIXEL(ray, SphereNormal, ray.ClosestSphere.Material, pnt);
			}

		}
   else {
			return ColorTriple();/// return background color
		}
}


bool CameraModel::HitsSomething(Ray &ray){
	bool HIT=false;
	 for (Sphere S : SPHs){
			   if (ray.RaySphereInterection(S) > 0){// checking if the ray actually hits the Sphere
				   HIT= true;
		   		}
			}

	 for(objFile object : OBJs){
			for(Face face : object.Faces ){
					if (ray.RayTriangleInterection(face)>0){// checking if the ray actually hits the face
						HIT= true;
					}
			}
	 }

	return HIT;
}

ColorTriple CameraModel:: COLOR_PIXEL(Ray &ray, Eigen::Vector3f &Normal, Materials &Mat, Eigen::Vector3f &pnt ){

	Eigen::MatrixXf Ka = Eigen::MatrixXf::Identity(3, 3); Ka(0,0)=Mat.KaRed; Ka(1,1)=Mat.KaGreen; Ka(2,2)=Mat.KaBlue;
	Eigen::MatrixXf Kd = Eigen::MatrixXf::Identity(3, 3); Kd(0,0)=Mat.KdRed; Kd(1,1)=Mat.KdGreen; Kd(2,2)=Mat.KdBlue;
	Eigen::MatrixXf Ks = Eigen::MatrixXf::Identity(3, 3); Ks(0,0)=Mat.KsRed; Ks(1,1)=Mat.KsGreen; Ks(2,2)=Mat.KsBlue;

	Eigen::Vector3f Illumination(0,0,0) ;
//I= AmbientLight + SUM( Diffuss Light + Specular Light)

//AmbientLight: Ka * Brightness of AmbientLight
	Illumination = Ka * Ambient.getVector();
	//cout<<"Ambient lighting "<< Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<" "<<endl;

	for( LightSource L : LightSourcesList ){
		 Eigen::Vector3f  X();
		  Ray shadow(pnt, L.getXYZvector().normalized());
		  if (!HitsSomething(shadow)){

					   Eigen::Vector3f lightS(L.getXYZvector() - pnt); lightS = lightS.normalized();
					   //this line ^^^ is differnt for spheres and triangles ==lightS( L.getXYZvector());

					   if(lightS.dot(Normal) > 0 ){// the light is NOT on the back side of the object
		//Diffuse :  kd * brighness of light scorce  * (L dot normal)
						Illumination +=  Kd * L.getBrightnessVector() * lightS.dot(Normal) ;
						//cout<<"Diffuse lighting "<<Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<" "<<endl;

		//Specular Illumination  : ks * brighness of light scorce * (2(N dot L )* N -L dot V )^phong
						Eigen::Vector3f toC  = ray.Pixel - pnt ; toC = toC.normalized();
						Eigen::Vector3f spR  = (2 * lightS.dot(Normal) * Normal) - lightS;

						float CdR  = toC.dot(spR);
						if (CdR > 0.0){
							Illumination +=  (Ks * L.getBrightnessVector()) * (pow(CdR ,Mat.phong));
							//cout<<"AFTER Specular  "<<endl;
							//cout<<Illumination(0)<<" "<<Illumination(1)<<" "<<Illumination(2)<<endl;
							}
					   }
		   	}
		}

    // write the resulting RGB into the pixel
	return ColorTriple(Illumination(0),Illumination(1),Illumination(2));

}

vector<vector<ColorTriple> > CameraModel:: Run(){

	vector<vector<ColorTriple> > FileColor;
	ColorTriple rgb;
	Eigen::Vector3f pixel, Direction;
	for(int x =0; x < height ; x++){
		vector<ColorTriple> temp;
		for(int y=0; y <width; y++){
		// for each pixel in the image to be rendered
			       //fire a ray into the scene and determine the first( the smallest  t value) visible surface
							    // for each pixel hit into each face
								pixel=pixelPt(x,y);
								Direction=pixel - EyeV.getVector(); //(pixel point)- eye

								Ray r(pixel,Direction);
								rgb = RAY_CAST(r);
							    temp.push_back(rgb);

		}//end of ForLoop y
		FileColor.push_back(temp);
	}//end of ForLoop x

	return FileColor;

}

CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}


void  CameraModel:: testP3(){
	for (Sphere s : SPHs){
		cout<<s.toString()<<endl;
	}
}

void CameraModel:: testP2(){

	/*
					cout<<"Testing variables from the Camera Model "<<endl;

					cout<<"EyeV "<< EyeV.toString() <<endl;
					cout<<"LookV "<< LookV.toString() <<endl;
					cout<<"UpV "<< UpV.toString() <<endl;

					cout<<"Wv "<< Wv.toString()<<endl;
					cout<<"Uv "<< Uv.toString()<<endl;
					cout<<"Vv "<< Vv.toString()<<endl;


					cout<<"near "<< near <<endl;
					cout<<"left "<< left <<endl;
					cout<<"right "<< right <<endl;
					cout<<"top "<< top <<endl;
					cout<<"bottom "<< bottom <<endl;
					cout<<"width "<< width <<endl;
					cout<<"height "<< height <<"\n\n"<<endl;

					cout<<"NUMBER OF LightSource:  "<< LightSourcesList.size()<<endl;
					for( int a = 0; a < LightSourcesList.size(); a++ ){
						cout<<"LightSource: x "<< LightSourcesList[a].x<<endl;
						cout<<"LightSource: y "<< LightSourcesList[a].y<<endl;
						cout<<"LightSource: z "<< LightSourcesList[a].z<<endl;
						cout<<"LightSource: w "<< LightSourcesList[a].w<<endl;
						cout<<"LightSource: red "<< LightSourcesList[a].red<<endl;
						cout<<"LightSource: green "<< LightSourcesList[a].green<<endl;
						cout<<"LightSource: blue "<< LightSourcesList[a].blue<<endl;
					}

					cout<<"AmbientLight.red " << Ambient.red<<endl;
					cout<<"AmbientLight.green " << Ambient.green<<endl;
					cout<<"AmbientLight.blue " << Ambient.blue<<"\n\n"<<endl;



					cout<<"NUMBER OF OBJs:  "<< OBJs.size()<<endl;
					for( int a = 0; a < OBJs.size(); a++ ){
						cout<<"NUMBER OF Faces:  "<< OBJs[a].Faces.size()<<endl;
						for( int b = 0; b < OBJs[a].Faces.size(); b++ ){
							cout<< OBJs[a].Faces[b].toString()<<endl;
						}
					}


					cout<< "\nTESTING pixelPt "<< endl;
					// still need to figure out left and top and near

					cout<< "pixelPt (0,0) should be 𝙿𝚇:−2 P𝚈:2 𝚙𝚒𝚡𝚙𝚝:[−2,2,170]"<< endl;
					cout<< pixelPt(0,0)<< endl;

					cout<< "pixelPt (2,2) should be 𝙿𝚇:−2/3 𝙿Y: 2/3 p𝚒𝚡𝚙𝚝:[−2/3,2/3,170]"<< endl;
					cout<< pixelPt(2,2)<< endl;


					cout<< "\n\nTESTING RayTriangleInterection from sage math  \n A(3,0,0)  B(0,3,0)  C(0,0,3) L(0,0,0) D(1,1,1) \n>>>> β=1/3,γ=1/3,t= sqrt(3"<< endl;
						Eigen::Vector3f A(3,0,0);
						Eigen::Vector3f B(0,3,0);
						Eigen::Vector3f C(0,0,3);

						Eigen::Vector3f L(0,0,0);//pixel
						Eigen::Vector3f D(1,1,1);//

					float T = RayTriangleInterection(L,D,A,B,C);

					 cout << "T " << T<< endl;


					cout<<"\n\nTesting RAY_CAST"<<endl;

					RAY_CAST(1,1);

					cout<<"\n\nTesting COLOR_PIXEL"<<endl;

					Ray r(pixelPt(1, 1), 2, pixelPt(1, 1)-EyeV.getVector());
					point aa(1,1,50);
					point bb(1,2,50);
					point cc(-1,2,50);
					Materials Mat ("cube_centered.mtl");
					Face face(aa,bb,cc,Mat);
					COLOR_PIXEL (r,face);
					*/

}
