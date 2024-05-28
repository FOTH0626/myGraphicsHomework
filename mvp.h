#ifndef MVP_H
#define MVP_H

#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>



inline double DEG2RAD(double degree){return degree * M_PI / 180.0;}

Eigen::Matrix3f getModelMatrix(Eigen::Matrix3f m);
Eigen::Matrix3f setModelMatrix(float scale,float xMove, float yMove,float rotation);

// Eigen::Matrix3f getViewMatrix();
// Eigen::Matrix3f setViewMatrix();

// Eigen::Matrix3f getProjectionMatrix();
// Eigen::Matrix3f setProjectionMatrix();

std::array<double,2> setGaussProjection(Eigen::Vector2f point);
//Eigen::Vector2f getGaussPeojection(Eigen::Vector2f point);


#endif // MVP_H