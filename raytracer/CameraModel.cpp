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

CameraModel::CameraModel(vector<string> &Driver, vector<LightSource> &LightS, class AmbientLight &Ambient, vector<objFile> &Objs) {
	LightSourcesList = LightS;
	AmbientLight = Ambient;
	OBJs = Objs;

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

				Eigen::Vector3f ev = EyeV.getVector();
				Eigen::Vector3f lv = LookV.getVector();
				Eigen::Vector3f upv = UpV.getVector();

				Eigen::Vector3f wv(0,0,0);
				Eigen::Vector3f uv(0,0,0);
				Eigen::Vector3f vv(0,0,0);

				wv << ev - lv;
				wv = wv.normalized();
				uv = upv.cross(wv);
				uv = uv.normalized();
				vv = wv.cross(uv);

				Wv = point(wv(0),wv(1),wv(2));
				Uv = point(uv(0),uv(1),uv(2));
				Vv = point(vv(0),vv(1),vv(2));

}

void CameraModel:: test(){
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

					cout<<"AmbientLight.red " << AmbientLight.red<<endl;
					cout<<"AmbientLight.green " << AmbientLight.green<<endl;
					cout<<"AmbientLight.blue " << AmbientLight.blue<<"\n\n"<<endl;



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

					 float* BGT = RayTriangleInterection(L,D,A,B,C);
					 cout<< "Beta "<<BGT[0]<<endl;
					 cout<< "Gamma "<<BGT[1]<<endl;
					 cout << "T " << BGT[2]<< endl;


					cout<<"\n\nTesting RAY_CAST"<<endl;

					RAY_CAST(pixelPt(1, 1), pixelPt(1, 1)-EyeV.getVector());

					cout<<"\n\nTesting COLOR_PIXEL"<<endl;
					/*
					Ray r(pixelPt(1, 1), 2, pixelPt(1, 1)-EyeV.getVector());
					point aa(1,1,50);
					point bb(1,2,50);
					point cc(-1,2,50);
					Materials Mat ("cube_centered.mtl");
					Face face(aa,bb,cc,Mat);
					COLOR_PIXEL (r,face);
					*/

}

Eigen::Vector3f CameraModel:: pixelPt(int i, int j){
    float px = (float)i/(width-1)*(right-left)+left;

    float py = (float)j/(height-1)*(bottom-top)+top;

    Eigen::Vector3f pixpt =  EyeV.getVector()
							+ (near * Wv.getVector())
							+ (px * Uv.getVector())
							+ (py * Vv.getVector());
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

			M =M.transpose().eval();
			M1=M1.transpose().eval();
			M2=M2.transpose().eval();
			M3=M3.transpose().eval();

			float beta = M1.determinant()/ M.determinant();
			float gamma = M2.determinant()/ M.determinant();
			float t = M3.determinant()/ M.determinant();
			float* returnArray = new float[3];
			returnArray[0]=	beta;returnArray[1]= gamma; returnArray[2]=t;

			return returnArray;
}

ColorTriple CameraModel:: RAY_CAST(Eigen::Vector3f pixel, Eigen::Vector3f Direction){

	float* BGT = new float[3];
	float minT = numeric_limits<float>::max();
	Face closestFace;
	bool HitsSomething = false;

				for( objFile object : OBJs){
					   	for(Face face : object.Faces ){

					   			Eigen::Vector3f A = face.A.getVector();
					   			Eigen::Vector3f B = face.B.getVector();
					   			Eigen::Vector3f C = face.C.getVector();

					   			BGT = RayTriangleInterection(pixel,Direction,A,B,C);
					   			float beta = BGT[0]; float gamma = BGT[1]; float t = BGT[2];
					   			if (beta >=0 && gamma >=0 && beta + gamma <=1 && t>0){// checking if the ray actually hits the face
					   				HitsSomething=true;
					   				if (t < minT){ // checking if its the first visible surface aka the Smallest T value
					   					minT = t;
					   					closestFace = face;
					   				}
					   			}
					   	}// end ForEach for Faces
					}//end ForEach for Objects

		if (HitsSomething){
			//cout<<"RAY_CAST :HitsSomething TRUE!!"<<endl;
			//cout<<"RAY_CAST: Pixel\n"<< pixel<<endl;
			//cout<<"RAY_CAST: Direction\n"<< Direction<<endl;
			//cout<<"RAY_CAST: MinT\n"<< minT<<endl;
			//cout<<"RAY_CAST: ClosestFace\n"<< closestFace.toString()<<endl;

			point p;
			Ray ray(p.Vector2Point(pixel), minT, p.Vector2Point(Direction));

			Eigen::Vector3f PointonFace; PointonFace = (pixel) + minT*(Direction);
			return COLOR_PIXEL(ray, closestFace);
		}
		else {

			return ColorTriple();/// return background color
		}
}


ColorTriple CameraModel:: COLOR_PIXEL(Ray ray, Face face ){

	if (ray.Direction.getVector().normalized().dot(face.normal) < 0){// normal is pointing to the inside of the object
		face.setNormal(-face.normal);// Flip the normal;
	}
	//I= kaBa + SUM( KdBd(N dot L) + specular Light)
	Eigen::Vector3f Illumination(0,0,0) ;

	Eigen::MatrixXf Ka = Eigen::MatrixXf::Identity(3, 3); Ka(0,0)=face.Material.KaRed; Ka(1,1)=face.Material.KaGreen; Ka(2,2)=face.Material.KaBlue;
	Eigen::MatrixXf Kd = Eigen::MatrixXf::Identity(3, 3); Kd(0,0)=face.Material.KdRed; Kd(1,1)=face.Material.KdGreen; Kd(2,2)=face.Material.KdBlue;

				// Ka * Brightness of AmbientLight
	Illumination = Ka * AmbientLight.getVector(); cout<<"Illumination Ambieint Light "<<Illumination(0) << " "<<Illumination(1) << " "<<Illumination(2) << endl;

    //for every light socurces :
	for( LightSource L : LightSourcesList ){
		//Compute red, green and blue based on illumination
			//Diffusse Illumination : kd * brighness of light scorce  *(L dot normal)(this is a scalar)

		   Eigen::Vector3f lightS =  L.getXYZvector();
		   lightS = lightS.normalized();
		     //toL = ptL - ptos; toL = toL / toL.norm()
		   Eigen::Vector3f norm= face.getNormal();

		   if( lightS.dot(norm) >= 0 )// the light is on the back side of the object
		    	Illumination +=  Kd * L.getBrightnessVector() * lightS.dot(norm) ;

	}

    // write the resulting RGB into the pixel
	return ColorTriple(Illumination(0),Illumination(1),Illumination(2));

}



vector<vector<ColorTriple> > CameraModel:: Run(){
	for(int x =0; x < height ; x++){
		vector<ColorTriple> temp;
		for(int y=0; y <width; y++){
		// for each pixel in the image to be rendered
			       //fire a ray into the scene and determine the first( the smallest  t value) visible surface

				// make this a RAY object:
					Eigen::Vector3f pixel = pixelPt(x,y);
				    Eigen::Vector3f Direction = (pixel - EyeV.getVector()); //(pixel point)- eye

				    // for each pixel hit into each face
				    ColorTriple rgb = RAY_CAST(pixel,Direction);
				    temp.push_back(rgb);

		}//end of ForLoop y
		FileColor.push_back(temp);
	}//end of ForLoop x

	return FileColor;

}




CameraModel::~CameraModel() {
	// TODO Auto-generated destructor stub
}

