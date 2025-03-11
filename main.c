#include"pixel.h"
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
//calculate the average of the r,g,b values in the domain individually.
//That is, average all r colors and give a result,
//all g colors and give a result,
//and all b colors and give a result. 
void average_colors(std::vector<Pixel>& pixel_list){
	float totalR =0.0, totalG=0.0,totalB=0.0;
	for (std::vector<Pixel>::iterator it = pixel_list.begin();
	it != pixel_list.end(); ++it) {
	    totalR += it->r;
			totalG += it->g;
			totalB += it->b;
	}

	int num_pixels = pixel_list.size();
	std::cout << "average of R: " << totalR / num_pixels << std::endl;
	std::cout << "average of G: " << totalG / num_pixels << std::endl;
	std::cout << "average of B: " << totalB / num_pixels << std::endl;
	
}
//flips all pixels vertically.
//For example, in the y-direction, pixel 600 should become pixel 0
//and pixel 0 should become pixel 600. 
//No modification in the x-direction. 
void flip_vertically(std::vector<Pixel>& pixel_list){
	int maxY= 600;
	for (std::vector<Pixel>::iterator it = pixel_list.begin();
	it != pixel_list.end(); ++it) {
			it->y = maxY - it->y; // Modify the y-coordinate to flip vertically
	}
}

void save_to_file(const std::vector<Pixel>& pixel_list,
const std::string& output_file) {
	std::ofstream outfile(output_file.c_str());
	if (!outfile){
		std::cout << "Error: Could not open file " << std::endl;
	}
	// Loop through each pixel and write it to the file
	for (std::vector<Pixel>::const_iterator it = pixel_list.begin();
	it != pixel_list.end(); ++it) {
	    outfile << it->x << ","
			<< it->y << ","
			<< it->r << ","
			<< it->g << ","
			<< it->b << "\n";
	}
	outfile.close();
}
int main(){
	std::vector<Pixel> pixel_list;
	std::string file_name ="pixels.dat";
	//open file
	std::ifstream infile(file_name.c_str());
	if(!infile){
		std::cout<<"error:could not open file"<<std::endl;
	}
	std::string line;

	while(std::getline(infile,line)){
		int pos=0;
		Pixel pixel;
		//get x
		pos=line.find(',');
		std::stringstream s_x(line.substr(0,pos));
		int x;
		s_x>>x;
		pixel.x=x;
		line=line.substr(pos+1);
		// get y
		pos = line.find(',');
		std::stringstream s_y(line.substr(0,pos));
		int y;
		s_y>>y;
		pixel.y=y;
		line = line.substr(pos + 1);
		// get r
		pos = line.find(',');
		std::stringstream s_r(line.substr(0,pos));
		float r;
		s_r>>r;
		pixel.r=r;
		line = line.substr(pos + 1);
		// get g
		pos = line.find(',');
		std::stringstream s_g(line.substr(0,pos));
		float g;
		s_g>>g;
	  pixel.g=g;
		line = line.substr(pos + 1);
		// get b
		std::stringstream s_b(line);
		float b;
		s_b>>b;
		pixel.b=b;
		// Add the pixel to the list
		pixel_list.push_back(pixel);
	}

	infile.close();
	average_colors(pixel_list);
	flip_vertically(pixel_list);
	save_to_file(pixel_list, "flipped.dat");
	return 0;

}
