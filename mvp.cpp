#include "mvp.h"
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include <array>
#include <cmath>
#include "constant.h"


Eigen::Matrix3f getModelMatrix(Eigen::Matrix3f m){
    return m;
};

Eigen::Matrix3f setModelMatrix(float scale,float xMove, float yMove,float rotation)
{   
    double angle =DEG2RAD(rotation);

    Eigen::Matrix3f modelScale;
    modelScale <<scale, 0, 0,
                0, scale, 0,
                0, 0, 1;

    Eigen::Matrix3f modelRotation1;
    modelRotation1 <<1,0,ScreenWidth/2,
                    0,1,ScreenHeight/2,
                    0,0,1;
    
    Eigen::Matrix3f modelRotation;
    modelRotation << cos(angle),-sin(angle),0,
                    sin(angle),cos(angle),0,
                    0,0,1;

    Eigen::Matrix3f modelRotation2;
    modelRotation2 <<1,0,-ScreenWidth/2,
                    0,1,-ScreenHeight/2,
                    0,0,1;
    
    Eigen::Matrix3f modelMove;
    modelMove <<1, 0, xMove,
                0, 1, yMove,
                0, 0, 1;

    Eigen::Matrix3f model = Eigen::Matrix3f::Identity();
    
    return  modelRotation1 * modelRotation * modelRotation2 *modelMove * modelScale * model;
    //return modelMove *modelRotation* modelScale;
};

// Eigen::Matrix3f getViewMatrix();
// Eigen::Matrix3f setViewMatrix();


// Eigen::Matrix3f getProjectionMatrix();
// Eigen::Matrix3f setProjectionMatrix();

// std::array<double,2> setGaussPeojection(Eigen::Vector2f point){
//     const double a = 6378137.0;  // WGS 84椭球体长半轴
//     const double f = 1 / 298.2572;  // 扁率

//     // 高斯投影中所选用的投影带宽   
//     const int ZoneWidth = 6; // 通常中国区域使用6度带

//     int ProjNo = int((point[0] + ZoneWidth / 2) / ZoneWidth);
//     double L = DEG2RAD(point[0] - ProjNo * ZoneWidth + ZoneWidth / 2); // 经度转换为弧度
//     double B = DEG2RAD(point[1]); // 纬度转换为弧度

//     double e2 = 2 * f - f * f;  // 第一偏心率平方
//     double e1 = (1.0 - sqrt(1 - e2)) / (1.0 + sqrt(1 - e2));
//     double ee = e2 / (1 - e2);  // 第二偏心率平方

//     double N = a / sqrt(1.0 - e2 * sin(B) * sin(B));
//     double T = tan(B) * tan(B);
//     double C = ee * cos(B) * cos(B);
//     double A = cos(B) * L;
//     double M = a * ((1 - e2 / 4 - 3 * e2 * e2 / 64 - 5 * e2 * e2 * e2 / 256) * B
//                     - (3 * e2 / 8 + 3 * e2 * e2 / 32 + 45 * e2 * e2 * e2 / 1024) * sin(2 * B)
//                     + (15 * e2 * e2 / 256 + 45 * e2 * e2 * e2 / 1024) * sin(4 * B)
//                     - (35 * e2 * e2 * e2 / 3072) * sin(6 * B));

//     double X = M + N * tan(B) * (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24
//                           + (61 - 58 * T + T * T + 600 * C - 330 * ee) * A * A * A * A * A * A / 720);
//     double Y = N * (A + (1 - T + C) * A * A * A / 6
//              + (5 - 18 * T + T * T + 14 * ee - 58 * T * ee) * A * A * A * A * A / 120) + 500000;
//     Y += 1000000 * ProjNo; // 加上带号的百万
//     //return Eigen::Vector2f(X/100000, Y/100000);

//     return {X/100000, Y/100000};
//     }


// 将经度longitude转换为弧度
double degToRad(double degree) {
    return degree * M_PI / 180.0;
}

// 高斯投影的正算公式
std::array<double,2> setGaussProjection(Eigen::Vector2f point) {
    const double a = 6378137.0;  // WGS 84椭球体长半轴
    const double f = 1 / 298.257223563;  // 扁率
    double L = degToRad(point[0]); // 经度转换为弧度
    double B = degToRad(point[1]); // 纬度转换为弧度

    double e2 = 2 * f - f * f;  // 第一偏心率平方
    double N = a / sqrt(1.0 - e2 * sin(B) * sin(B));
    double T = tan(B) * tan(B);
    double C = e2 * cos(B) * cos(B);
    double A = cos(B) * L;

    double M = a * ((1 - e2 / 4 - 3 * e2 * e2 / 64 - 5 * e2 * e2 * e2 / 256) * B
                    - (3 * e2 / 8 + 3 * e2 * e2 / 32 + 45 * e2 * e2 * e2 / 1024) * sin(2 * B)
                    + (15 * e2 * e2 / 256 + 45 * e2 * e2 * e2 / 1024) * sin(4 * B)
                    - (35 * e2 * e2 * e2 / 3072) * sin(6 * B));

    double X = M + N * tan(B) * (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24
                          + (61 - 58 * T + T * T + 600 * C - 330 * e2 * C) * A * A * A * A * A * A / 720);
    double Y = N * (A + (1 - T + C) * A * A * A / 6
             + (5 - 18 * T + T * T + 14 * e2 - 58 * T * e2) * A * A * A * A * A / 120) + 500000;

    // 缩放坐标以适应1080p分辨率
    X = X / 100000; // 示例缩放因子
    Y = (Y - 500000) / 100000; // 示例缩放因子，减去500000以移动原点
    return {X, Y};
}


// Eigen::Vector2f getGaussPeojection(Eigen::Vector2f point){
//     return point;
// };
