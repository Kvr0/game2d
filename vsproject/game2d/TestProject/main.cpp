#include <Windows.h>
#include "s4DxLib.h"
#include "s4String.h"
#include "s4BaseObject.h"
#include "s4Matrix.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) 
{
	auto vec0 = game2d::make_s4Vector(640, 480);

	if (!game2d::s4DxLib::init(vec0.at(0), vec0.at(1), L"Window"_s))return -1;

	while (game2d::s4DxLib::loop());

	game2d::s4DxLib::end();

	return 0;
}
