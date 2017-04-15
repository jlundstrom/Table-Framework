#ifdef WIN32
#include "Display.h"
#include "Draw.h"
#include <windows.h>
#include <time.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

struct Globals
{
	HINSTANCE hInstance;
	HWND hwnd;
	HDC   hdc;
	HGLRC hglrc;
	int width, height;
};

int i = 0;
clock_t LastRun;
clock_t LastDraw;
unsigned char DRAWN;
char FPS;
struct Globals g;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// OpenGL Refrence: https://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/

void display() {
	int x = 0; int y = 0;
	float width = 2.0f / WIDTH, height = 2.0f / HEIGHT;
	float x1, y1;
	Pixel col;

	glViewport(0, 0, g.width, g.height); // set viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0f, 1, 1000);

	// 3. viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 1,
		0, 0, 0,
		0, 1, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);

	for (x = 0; x < WIDTH; x++)
	{
		for (y = 0; y < HEIGHT; y++)
		{
			col = getPixel(x, y);
			glColor3f((float)col.R / 255.0f, (float)col.G / 255.0f, (float)col.B / 255.0f);
			x1 = -1.0f + (width * x);
			y1 = 1.0f - (height * (y + 1.0f));

			glVertex2f(x1, y1);
			glVertex2f(x1 + width, y1);
			glVertex2f(x1 + width, y1 + height);
			glVertex2f(x1, y1 + height);
		}
	}


	glEnd();

	SwapBuffers(g.hdc);
}

void Display_init() {
	int argc = 0;
	LastRun = clock();
	LastDraw = clock();

	g.hInstance = GetModuleHandle(NULL);

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = g.hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("TableEmulator");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	RegisterClass(&wc);

	RECT rect;
	SetRect(&rect, 50,  // left
		50,  // top
		850, // right
		450); // bottom

	g.width = rect.right - rect.left;
	g.height = rect.bottom - rect.top;

	// Adjust it.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

	g.hwnd = CreateWindow(TEXT("TableEmulator"),
		TEXT("Table Emulator!"),
		WS_OVERLAPPEDWINDOW,
		rect.left, rect.top,  // adjusted x, y positions
		rect.right - rect.left, rect.bottom - rect.top,  // adjusted width and height
		NULL, NULL,
		g.hInstance, NULL);

	if (g.hwnd == NULL)
	{
		FatalAppExit(NULL, TEXT("CreateWindow() failed!"));
	}

	ShowWindow(g.hwnd, 1);
	g.hdc = GetDC(g.hwnd);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// just its size
	pfd.nVersion = 1;							// always 1

	pfd.dwFlags = PFD_SUPPORT_OPENGL |			// OpenGL support - not DirectDraw
		PFD_DOUBLEBUFFER |						// double buffering support
		PFD_DRAW_TO_WINDOW;						// draw to the app window, not to a bitmap image

	pfd.iPixelType = PFD_TYPE_RGBA;		// red, green, blue, alpha for each pixel
	pfd.cColorBits = 24;                // 24 bit == 8 bits for red, 8 for green, 8 for blue.
										// This count of color bits EXCLUDES alpha.

	pfd.cDepthBits = 32;                // 32 bits to measure pixel depth.  That's accurate!

	int chosenPixelFormat = ChoosePixelFormat(g.hdc, &pfd);
	if (chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("ChoosePixelFormat() failed!"));
	}

	char b[100];

	int result = SetPixelFormat(g.hdc, chosenPixelFormat, &pfd);

	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}

	g.hglrc = wglCreateContext(g.hdc);

	wglMakeCurrent(g.hdc, g.hglrc);
}

MSG msg;
void Draw(void) {
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	else
	{
		if ((CLOCKS_PER_SEC / 31) < (clock() - LastRun))
		{
			LastRun = clock();
			display();
			DRAWN = 1;

			i++;
			if (i == 5) {
				i = 0;
				FPS = (float)5 * CLOCKS_PER_SEC / (clock() - LastDraw);
				LastDraw = clock();
			}
		}
	}
	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
		Beep(50, 10);
		return 0;
		break;

	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		// don't draw here.  would be waaay too slow.
		// draw in the draw() function instead.
		EndPaint(hwnd, &ps);
	}
	return 0;
	break;

	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}
#endif
