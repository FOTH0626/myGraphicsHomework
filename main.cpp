#include "TGAImage.h"
#include <Eigen/Eigen>
#include <array>
#include <vector>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include "rasterizer.h"
#include "mvp.h"
#include "constant.h"


int main(){

	static TGAImage image(ScreenWidth ,ScreenHeight , TGAImage::RGB);	
	Json::Reader reader;
	Json::Value root;
	Eigen::Matrix3f m =setModelMatrix(20,-1200,-25,0);

	std::ifstream in("../china.json", std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "Error opening file\n";
		return -1;
	}
	if (reader.parse(in, root))
	{
		for(unsigned int i =0; i !=root["features"].size(); ++i)
		{
			for(auto& coordinates : root["features"][i]["geometry"]["coordinates"])
			{	
				//auto length =static_cast<unsigned int>(root["features"][i]["geometry"]["coordinates"][j].size());
				//rasterPoints.resize(root["features"][i]["geometry"]["coordinates"][j].size());
				std::vector<std::array<double, 2>> rasterPoints;
				std::transform(coordinates.begin(),
				coordinates.end(), 
				back_inserter(rasterPoints),
				[](const Json::Value& coord) -> std::array<double, 2> {
                    return {coord[0].asDouble(), coord[1].asDouble()};  // 访问每个坐标对并转换为double
                });
				for ( int k=0; k != rasterPoints.size() - 1; ++k){
					Eigen::Vector2f drawPoint1 = Eigen::Vector2f (rasterPoints[k][0],rasterPoints[k][1]);
					Eigen::Vector2f drawPoint2 = Eigen::Vector2f (rasterPoints[k+1][0],rasterPoints[k+1][1]);
					//高斯克吕格投影无法实现出图，放弃
					//auto gaussPoint1 = setGaussProjection(drawPoint1);
					//auto gaussPoint2 = setGaussProjection(drawPoint2);
					//std::cout << gaussPoint1[0] << "  " << gaussPoint1[1] << std::endl;
					
					Eigen::Vector3f draw1 = getModelMatrix(m)*Eigen::Vector3f (drawPoint1[0],drawPoint1[1] ,1.0);
					Eigen::Vector3f draw2 = getModelMatrix(m)*Eigen::Vector3f (drawPoint2[0],drawPoint2[1] ,1.0);

					
					
					//drawPoint1 = Eigen::Vector2f(tempDrawPoint1[0],tempDrawPoint1[1]);
					//drawPoint2 = Eigen::Vector2f(tempDrawPoint2[0],tempDrawPoint2[1]);

					drawLine(image, Eigen::Vector2f(draw1[0],draw1[1]), 
					Eigen::Vector2f(draw2[0],draw2[1]), White);
				};
				//[root,i,j]() -> std::array<double,2> {return{root["features"][i]["geometry"]["coordinates"][j][][],0.0};}
				
			};
				// for(unsigned int k = 0 ; k != root["features"][i]["geometry"]["coordinates"][j].size(); ++k)
				// {
				// 	std::cout<< root["features"][i]["geometry"]["coordinates"][j][k][0].asDouble() << "  ";
				// 	std::cout << root["features"][i]["geometry"]["coordinates"][j][k][1].asDouble() <<std::endl;
				// }
		}
			image.flip_vertically();
			image.write_tga_file("../output/chinaMap.tga");
	};
//	drawLine(image, Eigen::Vector2f(0,0), Eigen::Vector2f(1920,1080), TGAColor(255,255,255,255));


	return 0;
}