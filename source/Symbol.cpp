#include "Symbol.hpp"

Symbol::Symbol() {
	char1 = L' ';
	char2 = L' ';
	textcolor = 7;
	backcolor = 0;
	endl = false;
}

Symbol::Symbol(bool endline) {
	char1 = L' ';
	char2 = L' ';
	textcolor = 7;
	backcolor = 0;
	endl = endline;
}

Symbol::Symbol(wchar_t character, short foreground_color, short background_color, bool endline) {
	char1 = character;
	char2 = character;
	textcolor = foreground_color;
	backcolor = background_color;
	endl = endline;
}

Symbol::Symbol(wchar_t character1, wchar_t character2, short foreground_color, short background_color) {
	char1 = character1;
	char2 = character2;
	textcolor = foreground_color;
	backcolor = background_color;
	endl = false;
}
