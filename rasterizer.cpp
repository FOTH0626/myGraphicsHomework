#include "TGAImage.h"
#include <Eigen/Eigen>
#include <cmath>

TGAColor white = TGAColor(255,255,255,255);

// Bresenham's line drawing algorithm
// Code taken from a stack overflow answer: https://stackoverflow.com/a/16405254
void drawLine(TGAImage &image, Eigen::Vector2f point1,Eigen::Vector2f point2, TGAColor drawColor){
    auto x1 = point1.x();
    auto y1 = point1.y();
    auto x2 = point2.x();
    auto y2 = point2.y();

    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;

    dx=x2-x1;
    dy=y2-y1;
    dx1=std::fabs(dx);
    dy1=std::fabs(dy);
    px=2*dy1-dx1;
    py=2*dx1-dy1;

    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=x1;
            y=y1;
            xe=x2;
        }
        else
        {
            x=x2;
            y=y2;
            xe=x1;
        }   
        Eigen::Vector2i point = Eigen::Vector2i(x, y);
        image.set(point.x(),point.y(),drawColor);
        for(i=0;x<xe;i++)
        {
            x=x+1;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y=y+1;
                }
                else
                {
                    y=y-1;
                }
                px=px+2*(dy1-dx1);
            }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
        image.set(point.x(),point.y(),drawColor);
        }
    }
    else
    {
        if(dy>=0)
        {
            x=x1;
            y=y1;
            ye=y2;
        }
        else
        {
            x=x2;
            y=y2;
            ye=y1;
        }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
            image.set(point.x(),point.y(),drawColor);
        for(i=0;y<ye;i++)
        {
            y=y+1;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x=x+1;
                }
                else
                {
                    x=x-1;
                }
                py=py+2*(dx1-dy1);
            }
//            delay(0);
            Eigen::Vector2f point = Eigen::Vector2f(x, y);
            image.set(point.x(),point.y(),drawColor);
        }
    }
}
