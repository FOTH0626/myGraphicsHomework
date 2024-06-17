#include "TGAImage.h"
#include "constant.h"
#include <Eigen/Eigen>
#include "rasterizer.h"
#include <iostream>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
// 计算点的区域代码
int computeCode(double x, double y,double xmin,double xmax,double ymin,double ymax) {
    int code = INSIDE;

    if (x < xmin)      // 点在裁剪矩形左侧
        code |= LEFT;
    else if (x > xmax) // 点在裁剪矩形右侧
        code |= RIGHT;
    if (y < ymin)      // 点在裁剪矩形下侧
        code |= BOTTOM;
    else if (y > ymax) // 点在裁剪矩形上侧
        code |= TOP;

    return code;
}

void cohenSutherland(int xmin, int xmax, int ymin, int ymax, double x1, double y1, double x2, double y2,TGAImage& image){
    drawLine(image,Eigen::Vector2f(xmin,ymin),Eigen::Vector2f(xmax,ymin),White);
    drawLine(image, Eigen::Vector2f(xmin,ymax), Eigen::Vector2f(xmax,ymax), White);
    drawLine(image, Eigen::Vector2f(xmin,ymin), Eigen::Vector2f(xmin,ymax), White);
    drawLine(image, Eigen::Vector2f(xmax,ymin), Eigen::Vector2f(xmax,ymax), White);

    int code1 = computeCode(x1, y1,xmin,xmax,ymin,ymax);
    int code2 = computeCode(x2, y2,xmin,xmax,ymin,ymax);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;// point inside the window both
            break;
        } else if (code1 & code2) {
            break;// two point at the same side 
        } else {
            double x, y;
            int codeOut;
            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;}
            else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;}
            else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;}
            else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1,xmin,xmax,ymin,ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2,xmin,xmax,ymin,ymax);
            }
        }
    }
    if (accept) {
        std::cout << "Line accepted from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";
        drawLine(image,Eigen::Vector2f(x1,y1),Eigen::Vector2f(x2,y2),Red);
    } else {
        std::cout << "Line rejected\n";
    }
    

}

int main ()
{
    TGAImage image(1920, 1080, TGAImage::RGB);
    cohenSutherland(560 ,1360 ,240 ,840 ,960 ,540 ,0 ,0 , image);
    //drawLine(image, Eigen::Vector2f(0,0), Eigen::Vector2f(960,540), Green);
    image.flip_vertically(); 
    image.write_tga_file("../cohenSutherland.tga");
    return 0;
}