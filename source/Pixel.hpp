#pragma once
#include <string>

class Pixel {
public:
	Pixel(const unsigned short int& init_type = 0, const unsigned short int& init_side = 0);
	void EditPixel(const unsigned short int& new_type, const unsigned short int& new_side);
	void TypePixel() const;

	unsigned short int type; // 0 = air 1 = solid
	unsigned short int side; // east-west[x] = 1 north-south[z] = 2 top-bottom[y] = 3 none/unknown/other = 0
};

