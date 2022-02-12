#pragma once
#ifndef _GAME2D_S4DXLIB_H_
#define _GAME2D_S4DXLIB_H_
#include "DxLib.h"
#include "s4String.h"
namespace game2d
{
	class s4DxLib
	{
	public:
		// DxLibの初期化処理
		static bool init(int _width, int _height, const tstring& _title)
		{
			SetOutApplicationLogValidFlag(FALSE);
			SetDoubleStartValidFlag(TRUE);

			ChangeWindowMode(TRUE);
			SetGraphMode(_width, _height, 32, 60);
			SetWindowText(_title.c_str());

			if (DxLib_Init() < 0)return false;

			SetDrawScreen(DX_SCREEN_BACK);

			return true;
		}

		// DxLibの終了処理
		static void end()
		{
			DxLib_End();
		}

		// DxLibのループ処理
		static bool loop()
		{
			return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
		}
	};
}
#endif // !_GAME2D_S4DXLIB_H_