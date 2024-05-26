#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include "TGAImage.h"


void drawLine(TGAImage &image, Eigen::Vector2f point1,Eigen::Vector2f point2,TGAColor);


#endif//RASTERIZER_H