#include <iostream>
#include <stdio.h>

using namespace std;

//Foreground Colors
const int F_DEFAULT=39;
const int F_WHITE=37;
const int F_RED=31;
const int F_BLUE=34;
const int F_GREEN=32;
const int F_YELLOW=33;
const int F_MAGENTA=35;
const int F_CYAN=36;
const int F_BLACK=30;

//Background Colors
const int BG_DEFAULT=49;
const int BG_BLACK=40;
const int BG_RED=41;
const int BG_GREEN=42;
const int BG_YELLOW=43;
const int BG_BLUE=44;
const int BG_MAGENTA=45;
const int BG_CYAN=46;
const int BG_WHITE=47;

//Erase in Display Paramaters
const int ED_END=0;
const int ED_BEGIN=1;
const int ED_ALL=0;

//Erase in Line Paramaters
const int EL_END=0;
const int EL_BEGIN=1;

class CSI
{
	
};
class Screen
{
	public:
		int width;
		int height;
		void clear();
		void render(int** buffer,int width,int height);
	private:
};
Screen getScreen();
void resetColor();
void cursorUp(int n);
void cursorDown(int n);
void cursorForward(int n);
void cursorBack(int n);
void cursorNextLine(int n);
void cursorPreLine(int n);
void setCursorPos(int x,int y);
void erase(int n);
void eraseLine(int n);
void scrollUp(int n);
void scrollDown(int n);
void hideCursor();
void showCursor();
//void printText(const int fColor, const int bgColor, const char* text,...);
void printBlock(const int color);

#ifdef __linux__
#define printText(fColor, bgColor, ...)       \
	(                                         \
		printf("\e[%d;%dm", fColor, bgColor), \
		printf(__VA_ARGS__),                  \
		resetColor())
#else

#define printText(fColor, bgColor, ...)       \
		printf(__VA_ARGS__)

#endif

#define printRed(...) \
	printText(F_RED, BG_DEFAULT, __VA_ARGS__)

#define printBlue(...) \
	printText(F_BLUE, BG_DEFAULT, __VA_ARGS__)

#define printGreen(...) \
	printText(F_GREEN, BG_DEFAULT, __VA_ARGS__)

#define printYellow(...) \
	printText(F_YELLOW, BG_DEFAULT, __VA_ARGS__)

#define printMagenta(...) \
	printText(F_MAGENTA, BG_DEFAULT, __VA_ARGS__)

#define printCyan(...) \
	printText(F_CYAN, BG_DEFAULT, __VA_ARGS__)

#define printWhite(...) \
	printText(F_WHITE, BG_DEFAULT, __VA_ARGS__)

#define printBlack(...) \
	printText(F_BLACK, BG_DEFAULT, __VA_ARGS__)
