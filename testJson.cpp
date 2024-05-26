// #include <json/json.h>
// #include <iostream>
// #include <fstream>
// #include <Eigen/Eigen>


// void readFileChinajson()
// {
// 	Json::Reader reader;
// 	Json::Value root;

// 	std::ifstream in("../china.json", std::ios::binary);
// 	std::ofstream out ("fuck.txt",std::ios::binary);
// 	if (!in.is_open())
// 	{
// 		std::cout << "Error opening file\n";
// 		return;
// 	}
// 	if (reader.parse(in, root))
// 	{
// 		for(unsigned int i =0; i !=root["features"].size(); ++i)
// 		{
// 			for(unsigned int j =0 ; j != root["features"][i]["geometry"]["coordinates"].size(); ++j)
// 			{
// 				for(unsigned int k = 0 ; k != root["features"][i]["geometry"]["coordinates"][j].size(); ++k)
// 				{
// 					std::cout << root["features"][i]["geometry"]["coordinates"][j][k][0].asDouble() << "  ";
// 					std::cout << root["features"][i]["geometry"]["coordinates"][j][k][1].asDouble() <<std::endl;
// 					out << root["features"][i]["geometry"]["coordinates"][j][k][0].asDouble() << "  ";
// 					out << root["features"][i]["geometry"]["coordinates"][j][k][1].asDouble() <<std::endl;

// 				}
// 			}
// 		}
// 		std::cout << std::endl;
// 		std::cout << "Reading Complete!" << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << "parse error\n" << std::endl;
// 	}
// 	in.close();
// }

// int main(){
// 	return 0;
// }