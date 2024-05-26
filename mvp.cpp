#include "mvp.h"
#include <Eigen/Eigen>


Eigen::Matrix3f getModelMatrix(Eigen::Matrix3f m){
    return m;
};

Eigen::Matrix3f setModelMatrix(float scale,float xMove, float yMove)
{
    Eigen::Matrix3f model = Eigen::Matrix3f::Identity();
    model <<scale, 0, xMove,
            0, scale, yMove,
            0, 0, 1;
    return model;
};

// Eigen::Matrix3f getViewMatrix();
// Eigen::Matrix3f setViewMatrix();


// Eigen::Matrix3f getProjectionMatrix();
// Eigen::Matrix3f setProjectionMatrix();
