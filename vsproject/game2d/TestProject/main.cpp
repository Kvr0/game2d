#include <Windows.h>
#include "DxWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	game2d::DxWindow window;
	if (!window.init(640,480,L"Window")) return -1;

	while (window.loop());

	window.end();

	return 0;
}