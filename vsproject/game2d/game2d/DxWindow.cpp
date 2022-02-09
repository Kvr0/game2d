#include "pch.h"
#include "DxWindow.h"
namespace game2d
{
	DxWindow::DxWindow()
	{
	}
	DxWindow::~DxWindow()
	{
	}
	bool DxWindow::init(int _width, int _height, const TCHAR* _title)
	{
		// ログ出力フラグ
		SetOutApplicationLogValidFlag(FALSE);

		// 画面サイズ
		SetGraphMode(_width, _height, 32, 60);

		// ウインドウタイトル
		SetMainWindowText(_title);

		// ウインドウモード
		ChangeWindowMode(TRUE);

		// DxLibの初期化
		if (DxLib_Init() < 0) return false;

		// 描画先画面を設定
		SetDrawScreen(DX_SCREEN_BACK);
		return true;
	}
	void DxWindow::end()
	{
		// DxLibの終了処理
		DxLib_End();
	}
	bool DxWindow::loop()
	{
		// メッセージ処理, 裏画面描画, 描画先画面初期化
		return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
	}
}