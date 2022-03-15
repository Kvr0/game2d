#pragma once
#ifndef _GAME2D_S4DXINPUT_H_
#define _GAME2D_S4DXINPUT_H_
#include "s4DxLib.h"
#include "s4BaseObject.h"
#include "s4MathMatrix.h"
#include <chrono>
#include <array>

namespace game2d
{
	// Button
	class s4Button : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Button, s4BaseObject>();
	private:
		bool m_state;
		std::chrono::system_clock::time_point m_pushed;
	public:
		s4Button()
			:m_state(false), m_pushed()
		{
		}

		operator bool() const
		{
			return m_state;
		}

		double push_t() const
		{
			return (m_state ? 1.0 : -1.0) * std::chrono::duration<double>(std::chrono::system_clock::now() - m_pushed).count();
		}

		void push()
		{
			m_state = true;
			m_pushed = std::chrono::system_clock::now();
		}
		void release()
		{
			m_state = false;
			m_pushed = std::chrono::system_clock::now();
		}
	};

	// Keyborad
	class s4DxKeyboard
	{
	private:
		static inline std::array<s4Button, 256> __keys;
	public:
		static void update()
		{
			// KeyState
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			for (size_t i = 0; i < 256u; i++)
			{
				if (buf[i] == 0 && __keys[i]) __keys[i].release();
				else if (buf[i] != 0 && !__keys[i]) __keys[i].push();
			}
		}

		static const std::array<s4Button, 256> keys()
		{
			return __keys;
		}
	};

	// Mouse
	class s4DxMouse
	{
	private:
		static inline s4MathVector<int, 2> __pos;
		static inline std::array<s4Button, 5> __buttons;
		static inline int __wheel = 0;
	public:
		static void update()
		{
			// Pos
			DxLib::GetMousePoint(&__pos[0], &__pos[1]);

			// Buttons
			auto minput = DxLib::GetMouseInput();
			for (int i = 0; i < 5; i++)
			{
				if (minput & (1 << i)) { if (!__buttons[i]) __buttons[i].push(); }
				else { if (__buttons[i]) __buttons[i].release(); }
			}

			// Wheel
			__wheel = DxLib::GetMouseWheelRotVol();
		}

		static const s4MathVector<int, 2>& pos()
		{
			return __pos;
		}
		static const std::array<s4Button, 5>& buttons()
		{
			return __buttons;
		}
		static const int& wheel()
		{
			return __wheel;
		}

		static void setDisplayFlag(bool _flag)
		{
			DxLib::SetMouseDispFlag(_flag ? TRUE : FALSE);
		}
		static void setPos(const s4MathVector<int, 2>& _p)
		{
			DxLib::SetMousePoint(_p[0], _p[1]);
			__pos = _p;
		}
	};

	// s4DxInput
	class s4DxInput
	{
	public:
		static void update()
		{
			s4DxKeyboard::update();
			s4DxMouse::update();
		}
	};
}

#endif // !_GAME2D_S4DXINPUT_H_
