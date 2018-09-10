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

	Eigen::MatrixXd getRST();

// Class varibles

private:

		Eigen::MatrixXd getRotate(float vector[], float theta);

		Eigen::MatrixXd getScale(float scale);

		Eigen::MatrixXd getTranslate(float vector[]);

		// Class varibles
		float* RotateV;
		float ThetaV;
		float ScaleV;
		float* TranslateV;

};

#endif /* TRANSFORMS_H_ */
