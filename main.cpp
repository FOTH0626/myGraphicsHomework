#include "TGAImage.h"
#include <Eigen/Eigen>
#include <array>
#include <vector>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include "rasterizer.h"
#include "mvp.h"

	

int main(){

    const int width = 3840;
	const int height = 2160;
	static TGAImage image(width ,height, TGAImage::RGB);	
	Json::Reader reader;
	Json::Value root;
	Eigen::Matrix3f m =setModelMatrix(40,-2000,-100);

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
					
					Eigen::Vector3f DrawPoint1 = getModelMatrix(m)*Eigen::Vector3f (drawPoint1[0],drawPoint1[1] ,1.0);
					Eigen::Vector3f DrawPoint2 = getModelMatrix(m)*Eigen::Vector3f (drawPoint2[0],drawPoint2[1] ,1.0);
					
					//drawPoint1 = Eigen::Vector2f(tempDrawPoint1[0],tempDrawPoint1[1]);
					//drawPoint2 = Eigen::Vector2f(tempDrawPoint2[0],tempDrawPoint2[1]);

					drawLine(image, Eigen::Vector2f(DrawPoint1[0],DrawPoint1[1]), 
					Eigen::Vector2f(DrawPoint2[0],DrawPoint2[1]), TGAColor(255,255,255,255));
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
			image.write_tga_file("output.tga");
	};
//	drawLine(image, Eigen::Vector2f(0,0), Eigen::Vector2f(1920,1080), TGAColor(255,255,255,255));


	return 0;
}