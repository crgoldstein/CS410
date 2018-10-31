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
	Transforms(double rotate[] ,double theta ,double scale , double translate[]);
	Transforms();
	virtual ~Transforms();

	Eigen::MatrixXd getRST();


// Class varibles
private:
		Eigen::MatrixXd getRotate(const double vector[], const double theta);

		Eigen::MatrixXd getScale(const double scale);

		Eigen::MatrixXd getTranslate(const double vector[]);

		//Class varibles
		double* RotateV;
		double ThetaV;
		double ScaleV;
		double* TranslateV;

};

#endif /* TRANSFORMS_H_ */
