#ifndef MVP_H
#define MVP_H

#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>

Eigen::Matrix3f getModelMatrix(Eigen::Matrix3f m);
Eigen::Matrix3f setModelMatrix(float scale,float xMove, float yMove);

// Eigen::Matrix3f getViewMatrix();
// Eigen::Matrix3f setViewMatrix();

// Eigen::Matrix3f getProjectionMatrix();
// Eigen::Matrix3f setProjectionMatrix();

#endif // MVP_H