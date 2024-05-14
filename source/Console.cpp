#include "Console.hpp"

#include <cstdlib>
#include <string>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
	#include <io.h>
	#include <fcntl.h>
	
	using namespace std;

	void Console::Sleep(const unsigned int& milliseconds) {
		SleepEx(milliseconds,false);
    }

	void Console::Clear() {
		wchar_t wchar = L' ';
		WORD atribute = 0x0000;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		DWORD width = csbi.dwSize.X;
		DWORD height = csbi.dwSize.Y;

		DWORD dwCharBytesWrtitten = 0;
		DWORD dwAtrBytesWrtitten = 0;
		FillConsoleOutputCharacter(hConsole, wchar, width * height, { 0,0 } , &dwCharBytesWrtitten);
		FillConsoleOutputAttribute(hConsole, atribute, width * height, { 0,0 }, &dwAtrBytesWrtitten);
	}

	char Console::GetKey() {
		if (_kbhit()) {
			return (char)(_getch());
		} else {
			return '\0';
		}
	}

	unsigned int Console::GetScreenHeight() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		unsigned int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		return columns;
	}

	unsigned int Console::GetScreenWidth() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		unsigned int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return rows;
	}

	void Console::WriteBackgroundCube(const unsigned int& alfa) {
		wchar_t alfa_0 = L'\u0020';
		wchar_t alfa_1 = L'\u2591';
		wchar_t alfa_2 = L'\u2592';
		wchar_t alfa_3 = L'\u2593';
		wchar_t alfa_4 = L'\u2588';

		wchar_t wtext;

		if (alfa == 0) {
			wtext = alfa_0;
		} else if (alfa == 1) {
			wtext = alfa_1;
		} else if (alfa == 2) {
			wtext = alfa_2;
		} else if (alfa == 3) {
			wtext = alfa_3;
		} else if (alfa == 4) {
			wtext = alfa_4;
		}
		
		SetBothCharacters(wtext);


		return;
	}

	void Console::Cout(const bool& empty) {
		Init();
		if (OUT_TYPE == 0) {
			_setmode(_fileno(stdout), _O_U16TEXT);
			if (OUTPUT != nullptr) {
				//*
				SetConsoleActiveScreenBuffer(Console::hConsole);
				const size_t height = OUTPUT->size();
				const size_t width = ( (*OUTPUT)[0][ (*OUTPUT)[0].size() - 1 ].endl ) ? (2 * (*OUTPUT)[0].size()) - 1 : (2 * (*OUTPUT)[0].size());
				const size_t max = width * height;

				wchar_t* screen = new wchar_t[max];
				auto n = 0;
				for (auto i1 = 0; i1 < height; i1++) {
					for (auto i2 = 0; i2 < width; i2 += 2) {
						screen[n] = (*OUTPUT)[i1][i2 / 2].char1;
						if ((*OUTPUT)[i1][i2 / 2].endl) {
							++n;
						} else {
							screen[n + 1] = (*OUTPUT)[i1][i2 / 2].char2;
							n += 2;
						}
					}
				}

				n = 0;
				WORD* atributes = new WORD[max];
				for (auto i1 = 0; i1 < height; i1++) {
					for (auto i2 = 0; i2 < width; i2 += 2) {
						WORD atr = atr_vals[ ((*OUTPUT)[i1][i2 / 2].textcolor) ][ ((*OUTPUT)[i1][i2 / 2].backcolor) ];
						atributes[n] = atr;
						if ((*OUTPUT)[i1][i2 / 2].endl) {
							++n;
						} else {
							atributes[n + 1] = atr;
							n += 2;
						}
					}
				}
				/*
				HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				short c_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
				short c_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
				short buf_width = csbi.dwSize.X;
				short buf_height = csbi.dwSize.Y;

				int a = SetConsoleScreenBufferSize(hOut, { buf_width, c_height } );
				if (a == 0) {
					DWORD e = GetLastError();
					//exit(e);
				}
				//*/
				//system("cls");
				DWORD dwCharBytesWrtitten = 0;
				DWORD dwAtrBytesWrtitten = 0;
				
				WriteConsoleOutputCharacter(hConsole, screen, max, { 0,0 }, &dwCharBytesWrtitten);
				WriteConsoleOutputAttribute(hConsole, atributes, max, { 0,0 }, &dwAtrBytesWrtitten);
				
				delete screen;
				delete atributes;
				//*/

				/*
				for (wstring s : (*OUTPUT) ) {
					wcout << s << "\n";
				}
				//*/
				
				if (empty) {
					EmptyOutput();
				}
			} else {
				
			}
			_setmode(_fileno(stdout), _O_TEXT);
		}
	}

	void Console::Init() {
		if (init) { return; }
		init = true;

		for (auto i1 = 0; i1 < 16; i1++) {
			for (auto i2 = 0; i2 < 16; i2++) {
				WORD val = 0x0000;

				if (i1 == 0) { val |= 0x0000; }
				if (i1 == 1) { val |= FOREGROUND_RED; }
				if (i1 == 2) { val |= FOREGROUND_GREEN; }
				if (i1 == 3) { val |= FOREGROUND_RED | FOREGROUND_GREEN; }
				if (i1 == 4) { val |= FOREGROUND_BLUE; }
				if (i1 == 5) { val |= FOREGROUND_RED | FOREGROUND_BLUE; }
				if (i1 == 6) { val |= FOREGROUND_BLUE | FOREGROUND_GREEN; }
				if (i1 == 7) { val |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; }


				if (i1 == 8) { val |= FOREGROUND_INTENSITY; }
				if (i1 == 9) { val |= FOREGROUND_RED | FOREGROUND_INTENSITY; }
				if (i1 == 10) { val |= FOREGROUND_GREEN | FOREGROUND_INTENSITY; }
				if (i1 == 11) { val |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; }
				if (i1 == 12) { val |= FOREGROUND_BLUE | FOREGROUND_INTENSITY; }
				if (i1 == 13) { val |= FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; }
				if (i1 == 14) { val |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; }
				if (i1 == 15) { val |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; }

				if (i2 == 0) { val |= 0x0000; }
				if (i2 == 1) { val |= BACKGROUND_RED; }
				if (i2 == 2) { val |= BACKGROUND_GREEN; }
				if (i2 == 3) { val |= BACKGROUND_RED | BACKGROUND_GREEN; }
				if (i2 == 4) { val |= BACKGROUND_BLUE; }
				if (i2 == 5) { val |= BACKGROUND_RED | BACKGROUND_BLUE; }
				if (i2 == 6) { val |= BACKGROUND_BLUE | BACKGROUND_GREEN; }
				if (i2 == 7) { val |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; }

				if (i2 == 8) { val |= BACKGROUND_INTENSITY; }
				if (i2 == 9) { val |= BACKGROUND_RED | BACKGROUND_INTENSITY; }
				if (i2 == 10) { val |= BACKGROUND_GREEN | BACKGROUND_INTENSITY; }
				if (i2 == 11) { val |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; }
				if (i2 == 12) { val |= BACKGROUND_BLUE | BACKGROUND_INTENSITY; }
				if (i2 == 13) { val |= BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY; }
				if (i2 == 14) { val |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY; }
				if (i2 == 15) { val |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; }

				atr_vals[i1][i2] = val;
			}
		}
	}

	WORD Console::atr_vals[16][16] = { { 0x0000 } };
#else
	#include <unistd.h>
	#include <locale>
	#include <conio.h>

	using namespace std;

	void Console::Sleep(const unsigned int& milliseconds) {
		usleep(milliseconds * 1000); // takes microseconds
	}

	void Console::Clear() {
		system("clear");
	}

	void Console::WriteBackgroundCube() {
		wchar_t white = L'\u0020';
		wchar_t light = L'\u2591';
		wchar_t grey = L'\u2592';
		wchar_t dark = L'\u2593';
		wchar_t black = L'\u2588';
		
		wstring wtext;

		if (alfa == 0) {
			wtext += alfa_0;
			wtext += alfa_0;
		}
		else if (alfa == 1) {
			wtext += alfa_1;
			wtext += alfa_1;
		}
		else if (alfa == 2) {
			wtext += alfa_2;
			wtext += alfa_2;
		}
		else if (alfa == 3) {
			wtext += alfa_3;
			wtext += alfa_3;
		}
		else if (alfa == 4) {
			wtext += alfa_4;
			wtext += alfa_4;
		}

		locale::global(locale(""));
		wcout.imbue(locale());

		if (OUT_TYPE == 0) {
			if (OUTPUT != nullptr) {
				(*OUTPUT)[ (*OUTPUT).size() - 1 ].append(wtext);
			} else {
				output_var[ output_var.size() - 1 ].append(wtext);
			}
		} else if (OUT_TYPE == 1) {
			wcout << wtext;
		} else if (OUT_TYPE == 2) {
			if (OUTPUT != nullptr) {
				wfout.open( (*OUTPUT)[0], ios_base::app);
				wfout << wtext;
				wfout.close();
			} else {
				wcout << wtext;
			}
		} else {
			wcout << wtext;
		}

		return;
	}

	void Console::Cout(const bool& empty) {
		if (OUT_TYPE == 0) {
			locale::global(locale(""));
			wcout.imbue(locale());
			if (OUTPUT != nullptr) {
				for ( wstring s : (*OUTPUT) ) {
					wcout << s << L'\n';
				}
				if (empty) {
					EmptyOutput();
				}
			} else {
				for ( wstring s : output_var ) {
					wcout << s << L'\n';
				}
				if (empty) {
					EmptyOutput();
				}
			}
		}
	}

	void Console::Fout(const char*& file, const bool& empty) {
		if (OUT_TYPE == 0) {
			locale::global(locale(""));
			wcout.imbue(locale());
			wfout.open(file, ios_base::app);
			if (OUTPUT != nullptr) {
				for (wstring s : (*OUTPUT) ) {
					wfout << s << L'\n';
				}
				if (empty) {
					EmptyOutput();
				}
			}
			else {
				for (wstring s : output_var) {
					wfout << s << L'\n';
				}
				if (empty) {
					EmptyOutput();
				}
			}
			wfout.close();
		}
	}

	void Console::Init() {
		if (init) { return; }
		init = true;
	}

#endif

void Console::EmptyOutput() {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			*OUTPUT = vector<vector<Symbol>>();
		} else {
			output_var = vector<vector<Symbol>>();
		}
	}
}

void Console::SetTwoCharacters(const wchar_t wchar1, const wchar_t wchar2) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[OUTPUT->size() - 1][(*OUTPUT)[OUTPUT->size() - 1].size() - 1].char1 = wchar1;
			(*OUTPUT)[OUTPUT->size() - 1][(*OUTPUT)[OUTPUT->size() - 1].size() - 1].char2 = wchar2;
		} else {
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].char1 = wchar1;
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].char2 = wchar2;
		}
	}
}

void Console::SetBothCharacters(const wchar_t wchar) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[OUTPUT->size() - 1][(*OUTPUT)[OUTPUT->size() - 1].size() - 1].char1 = wchar;
			(*OUTPUT)[OUTPUT->size() - 1][(*OUTPUT)[OUTPUT->size() - 1].size() - 1].char2 = wchar;
		} else {
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].char1 = wchar;
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].char2 = wchar;
		}
	}
}

bool Console::ReplaceTwoCharacters(const unsigned int x, const unsigned int y, const wchar_t wchar1, const wchar_t wchar2) {
	if ((*OUTPUT).size() <= y || (*OUTPUT)[y].size() <= x) { return false; }
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[y][x].char1 = (wchar1 == L'^') ? (*OUTPUT)[y][x].char1 : wchar1;
			(*OUTPUT)[y][x].char2 = (wchar2 == L'^') ? (*OUTPUT)[y][x].char2 : wchar2;
		}
		else {
			output_var[y][x].char1 = (wchar1 == L'^') ? output_var[y][x].char1 : wchar1;
			output_var[y][x].char2 = (wchar2 == L'^') ? output_var[y][x].char2 : wchar2;
		}
	}
	return true;
}

void Console::ReplaceBothCharacters(const unsigned int x, const unsigned int y, const wchar_t wchar) {
	if (wchar == '\0') { return; }
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[y][x].char1 = wchar;
			(*OUTPUT)[y][x].char2 = wchar;
		}
		else {
			output_var[y][x].char1 = wchar;
			output_var[y][x].char2 = wchar;
		}
	}
}

void Console::ReplaceTextColor(const unsigned int x, const unsigned int y, const short int& colornum) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[y][x].textcolor = colornum;
		}
		else {
			output_var[y][x].textcolor = colornum;
		}
	}
}

void Console::SwitchTextBackground(const unsigned int x, const unsigned int y) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			short int text = (*OUTPUT)[y][x].textcolor;
			(*OUTPUT)[y][x].textcolor = (*OUTPUT)[y][x].backcolor;
			(*OUTPUT)[y][x].backcolor = text;
		} else {
			short int text = output_var[y][x].textcolor;
			output_var[y][x].textcolor = output_var[y][x].backcolor;
			output_var[y][x].backcolor = text;
		}
	}
}

void Console::ReplaceBackgroundColor(const unsigned int x, const unsigned int y, const short int& colornum) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[y][x].backcolor = colornum;
		}
		else {
			output_var[y][x].backcolor = colornum;
		}
	}
}

void Console::NewSymbol() {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[OUTPUT->size() - 1].push_back(Symbol::Symbol());
		} else {
			output_var[output_var.size() - 1].push_back(Symbol::Symbol());
		}
	}
}

void Console::SetTextColor(const short int& colornum) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[OUTPUT->size() - 1][(*OUTPUT)[OUTPUT->size() - 1].size() - 1].textcolor = colornum;
		}
		else {
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].textcolor = colornum;
		}
	}
}

void Console::SetBackgroundColor(const short int& colornum) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			(*OUTPUT)[ OUTPUT->size() - 1 ][ (*OUTPUT)[OUTPUT->size() - 1].size() - 1 ].backcolor = colornum;
		} else {
			output_var[output_var.size() - 1][output_var[output_var.size() - 1].size() - 1].backcolor = colornum;
		}
	}
}

void Console::NewLine(bool half) {
	if (OUT_TYPE == 0) {
		if (OUTPUT != nullptr) {
			if (OUTPUT->size() > 0 && half) {
				(*OUTPUT)[OUTPUT->size() - 1].push_back(Symbol::Symbol(L' ', 7, 0, true));
			}
			OUTPUT->push_back({});
		} else {
			if (output_var.size() > 0 && half) {
				output_var[output_var.size() - 1].push_back(Symbol::Symbol(L' ', 7, 0, true));
			}
			output_var.push_back({});
		}
	}
}

bool Console::init = false;
vector<vector<Symbol>>* Console::OUTPUT = nullptr;
unsigned int Console::OUT_TYPE = 0;
vector<vector<Symbol>> Console::output_var;
HANDLE Console::hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);