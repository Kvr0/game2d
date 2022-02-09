#pragma once
namespace game2d
{
	class DxWindow
	{
	public:
		DxWindow();
		virtual ~DxWindow();

		// 初期化処理 -> 成功判定
		//  _width, _height		:画面サイズ
		//  _title			:ウインドウタイトル
		bool init(int _width, int _height, const TCHAR* _title);

		// 終了処理
		void end();

		// ループ処理 -> ループ継続
		bool loop();
	};
}