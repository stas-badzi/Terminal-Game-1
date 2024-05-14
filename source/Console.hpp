/* COLORS
* 
	BLACK = 0;
	RED = 1;
	GREEN = 2;
	YELLOW = 3;
	BLUE = 4;
	MAGENTA = 5;
	CYAN = 6;
	WHITE = 7;

	LIGHT_BLACK = 8;
	LIGHT_RED = 9;
	LIGHT_GREEN = 10;
	LIGHT_YELLOW = 11;
	LIGHT_BLUE = 12;
	LIGHT_MAGENTA = 13;
	LIGHT_CYAN = 14;
	LIGHT_WHITE = 15;

*/
#pragma once

#include "Symbol.hpp"

#include <string>
#include <vector>

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#endif

class Console {
public:
	static unsigned int GetScreenWidth();
	static unsigned int GetScreenHeight();

	static char GetKey();

	static void Init();
	static void Clear();
	static void Sleep(const unsigned int& milliseconds);

	static std::vector< std::vector<Symbol> > * OUTPUT;
	static char* file;
	static unsigned int OUT_TYPE;

	static void Cout(const bool& empty = true);

	static void EmptyOutput();
	static void NewSymbol();
	static void NewLine(bool half = false);

	static void SetTwoCharacters(const wchar_t wchar1, const wchar_t wchar2);
	static void SetBothCharacters(const wchar_t wchar);
	static void SetTextColor(const short int& colornum);
	static void SetBackgroundColor(const short int& colornum);
	static void WriteBackgroundCube(const unsigned int& alfa = 4);

	static void SwitchTextBackground(const unsigned int x, const unsigned int y);
	static void ReplaceBothCharacters(const unsigned int x, const unsigned int y, const wchar_t wchar);
	static bool ReplaceTwoCharacters(const unsigned int x, const unsigned int y, const wchar_t wchar1, const wchar_t wchar2);
	static void ReplaceTextColor(const unsigned int x, const unsigned int y, const short int& colornum);
	static void ReplaceBackgroundColor(const unsigned int x, const unsigned int y, const short int& colornum);

	
private:
	static bool init;
#ifdef _WIN32
	static WORD atr_vals[16][16];
#endif
	static HANDLE hConsole;
	static std::vector< std::vector<Symbol> > output_var;
};