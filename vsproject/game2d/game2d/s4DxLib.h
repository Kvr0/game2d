#pragma once
#ifndef _GAME2D_DXWINDOW_H_
#define _GAME2D_DXWINDOW_H_
#include "DxLib.h"
namespace game2d
{
	class s4DxLib
	{
	public:
		// DxLib�̏���������
		static bool init(int _width, int _height, const TCHAR* _title)
		{
			SetOutApplicationLogValidFlag(FALSE);
			SetDoubleStartValidFlag(TRUE);

			ChangeWindowMode(TRUE);
			SetGraphMode(_width, _height, 32, 60);
			SetWindowText(_title);

			if (DxLib_Init() < 0)return false;

			SetDrawScreen(DX_SCREEN_BACK);

			return true;
		}

		// DxLib�̏I������
		static void end()
		{
			DxLib_End();
		}

		// DxLib�̃��[�v����
		static bool loop()
		{
			return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
		}
	};
}
#endif // !_GAME2D_DXWINDOW_H_