#include <Windows.h>
#include "game2d.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) 
{
	auto vec0 = game2d::make_s4Vector(640, 480);

	if (!game2d::s4DxLib::init(vec0.at(0), vec0.at(1),game2d::toString("Test"))) return -1;

	float h = 0.0f;

	while (game2d::s4DxLib::loop())
	{
		h += 1.0f / 360.0f;
		if (h > 1.0f)h -= 1.0f;

		auto h1 = h + 0.5f;
		if (h1 > 1.0f) h1 -= 1.0f;

		game2d::s4DxRenderShape::box({ 0,0 }, { 640,480 }, game2d::s4ColorHSV(h1, 1.0f, 1.0f), true);
		game2d::s4DxRenderString::string({10,10}, game2d::toString("Hello World", 100, 0.01), game2d::s4ColorHSV(h, 1.0f, 1.0f));
	}

	game2d::s4DxLib::end();

	return 0;
}
