/*
 * Transforms.h
 *
 *  Created on: Sep 6, 2018
 *      Author: Claire Goldstein
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
		Eigen::MatrixXf getRotate(const float vector[], const float theta);

		Eigen::MatrixXf getScale(const float scale);

		Eigen::MatrixXf getTranslate(const float vector[]);

		//Class varibles
		float* RotateV;
		float ThetaV;
		float ScaleV;
		float* TranslateV;

};

#endif /* TRANSFORMS_H_ */
