#pragma once
class Symbol {
public:
	Symbol();
	Symbol(bool endline);
	Symbol(wchar_t character, short foreground_color = 7, short background_color = 0, bool endline = false);
	Symbol(wchar_t character1, wchar_t character2, short foreground_color = 7, short background_color = 0);

	bool endl;
	wchar_t char1;
	wchar_t char2;
	short textcolor;
	short backcolor;
};

