#include "Pixel.hpp"
#include "Console.hpp"

#include <iostream>

using namespace std;

Pixel::Pixel(const unsigned short int& init_type, const unsigned short int& init_side) {
	type = init_type;
	side = init_side;
}

void Pixel::EditPixel(const unsigned short int& new_type, const unsigned short int& new_side) {
	type = new_type;
	side = new_side;
}

void Pixel::TypePixel() const {
	Console::NewSymbol();
	if (type == 0) {
		Console::SwitchTextBackground((*Console::OUTPUT)[Console::OUTPUT->size() - 1].size() - 1, Console::OUTPUT->size() - 1);
		Console::WriteBackgroundCube(4);
	} else if (type >= 1) {
		if (side == 0) {
			Console::SetBackgroundColor(15);
			Console::SetTextColor(6);
			Console::WriteBackgroundCube(0);
		} else if (side == 1) {
			Console::SetBackgroundColor(15);
			Console::SetTextColor(12);
			Console::WriteBackgroundCube(3);
		} else if (side == 2) {
			Console::SetBackgroundColor(14);
			Console::SetTextColor(12);
			Console::WriteBackgroundCube(4);
		} else if (side == 3) {
			Console::SetBackgroundColor(0);
			Console::SetTextColor(12);
			Console::WriteBackgroundCube(3);
		}
	}
	Console::ReplaceTwoCharacters((*Console::OUTPUT)[Console::OUTPUT->size() - 1].size() - 1, Console::OUTPUT->size() - 1, to_wstring(type)[0], to_wstring(side)[0]);

	return;
}
