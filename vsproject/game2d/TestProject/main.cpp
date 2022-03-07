#include <Windows.h>
#include "game2d.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) 
{
	auto vec0 = game2d::make_s4Vector(640, 480);

	if (!game2d::s4DxLib::init(vec0.at(0), vec0.at(1),game2d::toString("Test"))) return -1;

	std::vector<game2d::s4DxVertex> vertex;
	vertex.push_back(game2d::s4DxVertex({ 10.0f, 10.0f }, game2d::s4ColorF(1.0f, 1.0f, 1.0f)));
	vertex.push_back(game2d::s4DxVertex({ 110.0f, 10.0f }, game2d::s4ColorF(1.0f, 1.0f, 1.0f)));
	vertex.push_back(game2d::s4DxVertex({ 110.0f, 110.0f }, game2d::s4ColorF(1.0f, 1.0f, 1.0f)));
	vertex.push_back(game2d::s4DxVertex({ 10.0f, 110.0f }, game2d::s4ColorF(1.0f, 1.0f, 1.0f)));

	auto prim = game2d::s4DxPrimitive(vertex, {0,1,2,0,2,3}, game2d::s4DxPrimitive::Type::TriangleList);

	float hue = 0.0f;

	while (game2d::s4DxLib::loop())
	{
		hue += 1.0f / 360.0f;
		if (hue > 1.0f) hue -= 1.0f;

		prim.vertex[0].dif = game2d::s4ColorHSV(hue, 1.0f, 1.0f).getCOLOR_U8();
		prim.vertex[1].dif = game2d::s4ColorHSV(hue + 0.25f + (hue + 0.25f > 1.0f ? -1.0f : 0.0f), 1.0f, 1.0f).getCOLOR_U8();
		prim.vertex[2].dif = game2d::s4ColorHSV(hue + 0.5f + (hue + 0.5f > 1.0f ? -1.0f : 0.0f), 1.0f, 1.0f).getCOLOR_U8();
		prim.vertex[3].dif = game2d::s4ColorHSV(hue + 0.75f + (hue + 0.75f > 1.0f ? -1.0f : 0.0f), 1.0f, 1.0f).getCOLOR_U8();

		prim.render();
	}

	game2d::s4DxLib::end();

	return 0;
}
