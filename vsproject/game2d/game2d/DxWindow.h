#pragma once
namespace game2d
{
	class DxWindow
	{
	public:
		DxWindow();
		virtual ~DxWindow();

		// ���������� -> ��������
		//  _width, _height		:��ʃT�C�Y
		//  _title			:�E�C���h�E�^�C�g��
		bool init(int _width, int _height, const TCHAR* _title);

		// �I������
		void end();

		// ���[�v���� -> ���[�v�p��
		bool loop();
	};
}