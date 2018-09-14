/*
 * Transforms.h
 *
 *  Created on: Sep 6, 2018
 *      Author: clairegoldstein
 */

#ifndef TRANSFORMS_H_
#define TRANSFORMS_H_
#include <Eigen/Dense>


class Transforms {

public:
//Constructors
	Transforms(float rotate[] ,float theta ,float scale , float translate[]);
	Transforms();
	virtual ~Transforms();

	Eigen::MatrixXf getRST();


// Class varibles
private:

		Eigen::MatrixXf getRotate(float vector[], float theta);

		Eigen::MatrixXf getScale(float scale);

		Eigen::MatrixXf getTranslate(float vector[]);

		//Class varibles
		float* RotateV;
		float ThetaV;
		float ScaleV;
		float* TranslateV;

};

#endif /* TRANSFORMS_H_ */
