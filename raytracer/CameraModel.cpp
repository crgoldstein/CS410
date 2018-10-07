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



using namespace std;

CameraModel::CameraModel() {}

CameraModel::CameraModel(vector<string> &Driver, vector<LightSource> &LightS, class AmbientLight &Ambient, vector<string> &Objs) {

	LightSources = LightS;
	AmbientLight = Ambient;
	OBJs = Objs;

	Eigen::Vector3f ev(0,0,0);
	Eigen::Vector3f lv(0,0,0);
	Eigen::Vector3f upv(0,0,0);

				for (int i =  0; i < Driver.size(); i++)
				{
					vector<string> line;
					boost::split(line, Driver[i] ,boost::is_any_of(" "));

					if (line.size() ==4){
							float a =stof((line[1]).c_str(),0);
							float b = stof((line[2]).c_str(),0);
							float c = stof((line[3]).c_str(),0);

							if (line[0].compare("eye")==0){
								EyeV[0] = a;
								EyeV[1] = b;
								EyeV[2] =c;
								ev << a, b, c;
							}
							else if(line[0].compare("look")==0){
								LookV[0] = a;
								LookV[1] = b;
								LookV[2] = c;
								lv << a, b, c;

							}
							else if(line[0].compare("up")==0){
								UpV[0] = a;
								UpV[1] = b;
								UpV[2] = c;
								upv << a, b, c;
							}

					}
					else if(line[0].compare("d")==0)
					{
						near = EyeV[2]-strtof((line[1]).c_str(),0);
						//from the eye in the z direction to the near clippping plane

					}
					else if(line[0].compare("bounds")==0)
					{
						left = strtof((line[1]).c_str(),0);
						right = strtof((line[2]).c_str(),0);
						top = strtof((line[3]).c_str(),0);
						bottom = strtof((line[3]).c_str(),0);

					}
					else if(line[0].compare("bounds")==0)
					{
						width = strtof((line[1]).c_str(),0);
						height = strtof((line[2]).c_str(),0);

					}
				}// end of driver for loop

				Eigen::Vector3f wv(0,0,0);
				Eigen::Vector3f uv(0,0,0);
				Eigen::Vector3f vv(0,0,0);

				wv << ev - lv;
				wv = wv.normalized();
				uv = upv.cross(wv);
				uv = uv.normalized();
				vv = wv.cross(uv);

				this->Wv[0] =wv(0); this->Wv[1]=wv(1); this->Wv[2]=wv(2);
				this->Uv[0] =uv(0); this->Uv[1]=uv(1); this->Uv[2]=uv(2);
				this->Vv[0] =vv(0); this->Vv[1]=vv(1); this->Vv[2]=vv(2);

				test();


}


void CameraModel:: test(){
					cout<<"Testing variables from the Camera Model "<<endl;

					Eigen::Vector3f ev(EyeV[0],EyeV[1],EyeV[2]);
					Eigen::Vector3f lv(LookV[0],LookV[1],LookV[2]);
					Eigen::Vector3f upv(UpV[0],UpV[1],UpV[2]);

					Eigen::Vector3f wv(Wv[0],Wv[1],Wv[2]);
					Eigen::Vector3f uv(Uv[0],Uv[1],Uv[2]);
					Eigen::Vector3f vv(Vv[0],Vv[1],Vv[2]);

					cout<<"EyeV "<< ev<< endl;
					cout<<"LookV \n"<< lv<<endl;
					cout<<"UpV \n"<< upv<<endl;

					cout<<"Wv \n"<< wv<<endl;
					cout<<"Uv \n"<< uv<<endl;
					cout<<"Vv \n"<< vv<<endl;

					cout<<"near "<< near <<endl;
					cout<<"left "<< left <<endl;
					cout<<"right "<< right <<endl;
					cout<<"top "<< top <<endl;
					cout<<"bottom "<< bottom <<endl;
					cout<<"width "<< width <<endl;
					cout<<"height "<< height <<endl;

					for( int a = 0; a < LightSources.size(); a++ ){

						cout<<"LightSource: x "<< LightSources[a].x<<endl;
						cout<<"LightSource: y "<< LightSources[a].y<<endl;
						cout<<"LightSource: z "<< LightSources[a].z<<endl;
						cout<<"LightSource: w "<< LightSources[a].w<<endl;
						cout<<"LightSource: red "<< LightSources[a].red<<endl;
						cout<<"LightSource: green "<< LightSources[a].green<<endl;
						cout<<"LightSource: blue "<< LightSources[a].blue<<endl;

					}
					cout<<"AmbientLight.red " << AmbientLight.red<<endl;
					cout<<"AmbientLight.green " << AmbientLight.green<<endl;
					cout<<"AmbientLight.blue " << AmbientLight.blue<<endl;


					for( int a = 0; a < OBJs.size(); a++ ){
						cout<<"Object: " << OBJs[a]<<endl;
					}

					cout<< "TESTING pixelPt "<< endl;
					// still need to figure out left and top and near

					cout<< "TESTING RayTriangleInterection "<< endl;
					Eigen::Vector3f A(3,0,0);
					Eigen::Vector3f B(0,3,0);
					Eigen::Vector3f C(0,0,3);
					Eigen::Vector3f L(0,0,0);
					Eigen::Vector3f D(1,1,1);
					float BGT[] = RayTriangleInterection(L,D,A,B,C);
					cout<< "Beta "<<BGT[0]<<endl;
					cout<< "Gamma "<<BGT[2]<<endl;
					cout << "T "<< BGT[2]<< endl;


}

Eigen::Vector3f CameraModel:: pixelPt(int i, int j){
    double px = i/(width-1)*(right-left)+left;
    double py = j/(height-1)*(bottom-top)+top;

    Eigen::Vector3f ev(EyeV[0],EyeV[1],EyeV[2]);
    Eigen::Vector3f wv(Wv[0],Wv[1],Wv[2]);
    Eigen::Vector3f uv(Uv[0],Uv[1],Uv[2]);
    Eigen::Vector3f vv(Vv[0],Vv[1],Vv[2]);

    Eigen::Vector3f pixpt = ev + (near * wv) + (px * uv) + (py * vv);

    cout<<"near "<< near <<endl;
    cout<<"px"<< px<<endl;
    cout<<"py"<< py<<endl;
    cout<<"pixpt"<< pixpt<<endl;

    return pixpt;

}

float* CameraModel:: RayTriangleInterection(Eigen::Vector3f &L, Eigen::Vector3f &D, Eigen::Vector3f &A, Eigen::Vector3f &B ,Eigen::Vector3f &C){
	//Cramer's Rule.
	//This approach involves solving for the determinants of four matrices,
	//the original M matrix and then three derived by substituting Y into successive columns.
			D=D.normalized().eval();

			Eigen::Vector3f AminusL = A-L;
			Eigen::Matrix3f M;   M << (A-B)   ,(A-C),   D;
			Eigen::Matrix3f M1; M1 << AminusL ,(A-C),   D;
			Eigen::Matrix3f M2; M2 << (A-B)   ,AminusL, D;
			Eigen::Matrix3f M3; M3 << (A-B)   ,(A-C),   AminusL;

			float beta = M1.determinant()/ M.determinant();
			float gamma = M2.determinant()/ M.determinant();
			float t = M3.determinant()/ M.determinant();

			return {beta,gamma,t};
}

void CameraModel:: Run(){
	for(int x =0; x< width; x++ ){
		for(int y=0; y<height; y++){// for each pixel in the image to be rendered

			//fire a ray into the scene and determine the first visible surface
		            Eigen::Vector3f L = pixelPt(x,y);
					//Eigen::Vector3f D = Direction?  is this the look at point - (pizel point)L?
				//From OBJ file: ???
					//Eigen::Vector3f A:
					//Eigen::Vector3f B:
					//Eigen::Vector3f C:
				//float BGT[] = RayTriangleInterection(L,D,A,B,C);



				//if hitting a point on a surface # If Beta+ Gamma !>1 and B G and T <1
					//which lights sources illuminate that point
					//Compute red, green and blue based on illumination
					// write the resulting RGB into the pixel
				//Else
				// Write background RGB into pixel
		}
	}
}




CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}

