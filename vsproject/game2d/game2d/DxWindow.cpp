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
		// ���O�o�̓t���O
		SetOutApplicationLogValidFlag(FALSE);

		// ��ʃT�C�Y
		SetGraphMode(_width, _height, 32, 60);

		// �E�C���h�E�^�C�g��
		SetMainWindowText(_title);

		// �E�C���h�E���[�h
		ChangeWindowMode(TRUE);

		// DxLib�̏�����
		if (DxLib_Init() < 0) return false;

		// �`����ʂ�ݒ�
		SetDrawScreen(DX_SCREEN_BACK);
		return true;
	}
	void DxWindow::end()
	{
		// DxLib�̏I������
		DxLib_End();
	}
	bool DxWindow::loop()
	{
		// ���b�Z�[�W����, ����ʕ`��, �`����ʏ�����
		return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
	}
}