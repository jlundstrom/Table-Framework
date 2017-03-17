#ifdef WIN32
#include "Display.h"
#include "Draw.h"
#include <windows.h>
#include <time.h>

#define	BLUE 0x10
#define	GREEN 0x20
#define	RED 0x40
#define	LIGHTBLUE 0x90
#define	LIGHTGREEN 0xA0
#define	LIGHTRED 0xC0
#define WHITE 0xF0

HANDLE Handle;
int i = 0;
clock_t LastRun;
unsigned char DRAWN;
char FPS;

void Display_init() {
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(65001);
	LastRun = clock();
}

void Draw(void) {
	int x, y;
	COORD t;
	unsigned char color;
	DWORD size = 2;
	DWORD  ret;
	Pixel pixel;


	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			color = 0;
			t.X = x * 2;
			t.Y = y;

			pixel = getPixel(x, y);

			if (pixel.R > 128) {
				color |= RED;
			}
			else if (pixel.R > 0) {
				color |= LIGHTRED;
			}
			if (pixel.G > 128) {
				color |= GREEN;
			}
			else if (pixel.G > 0) {
				color |= LIGHTGREEN;
			}
			if (pixel.B > 128) {
				color |= BLUE;
			}
			else if (pixel.B > 0) {
				color |= LIGHTBLUE;
			}

			FillConsoleOutputCharacter(Handle, (TCHAR) '█', size, t, &ret);
			FillConsoleOutputAttribute(Handle, color, size, t, &ret);
		}
	}
	color = WHITE;
	t.Y = HEIGHT;
	for (x = 0; x < WIDTH + 1; x++) {
		t.X = x * 2;
		FillConsoleOutputCharacter(Handle, (TCHAR) '█', size, t, &ret);
		FillConsoleOutputAttribute(Handle, color, size, t, &ret);
	}
	t.X = WIDTH * 2;
	for (y = 0; y < HEIGHT + 1; y++) {
		t.Y = y;
		FillConsoleOutputCharacter(Handle, (TCHAR) '█', size, t, &ret);
		FillConsoleOutputAttribute(Handle, color, size, t, &ret);
	}
	t.X = 0;
	t.Y = y;
	SetConsoleCursorPosition(Handle, t);
	
	i++;
	if (i == 5) {
		i = 0;
		FPS = (float)5 * CLOCKS_PER_SEC / (clock() - LastRun);
		LastRun = clock();
	}
	DRAWN = 1;
}
#endif
