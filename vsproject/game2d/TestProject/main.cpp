#include <Windows.h>
#include "s4DxLib.h"
#include "s4String.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) 
{

	game2d::s4String title = L"Hello"_s + L"World"_s;

	if (!game2d::s4DxLib::init(640,480, title))return -1;

	while (game2d::s4DxLib::loop());

	game2d::s4DxLib::end();

	return 0;
}
