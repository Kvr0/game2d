#pragma once
#ifndef _GAME2D_S4COLOR_H_
#define _GAME2D_S4COLOR_H_
#include "s4BaseObject.h"
#include <variant>
#include <array>

namespace game2d
{
	class s4ColorBase : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4ColorBase, s4BaseObject>();
	public:
		virtual unsigned int getUInt() const = 0;
		virtual std::array<unsigned char, 3> getUChar() const = 0;
		virtual std::array<float, 3> getFloat() const = 0;
	};

	class s4Color : public s4ColorBase
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Color, s4ColorBase>();
	public:
		unsigned value;
		s4Color(unsigned _col)
			:value(_col)
		{}
		s4Color(unsigned char _r, unsigned char _g, unsigned char _b)
			:value(((unsigned)_r << 16) + ((unsigned)_g << 8) + ((unsigned)_b))
		{
		}
		s4Color(const std::array<unsigned char, 3>& _col)
			:s4Color(_col[0],_col[1],_col[2])
		{
		}
		s4Color(const s4ColorBase& _col)
			:value(_col.getUInt())
		{}

		virtual unsigned int getUInt() const
		{
			return value;
		}
		virtual std::array<unsigned char, 3> getUChar() const
		{
			return { static_cast<unsigned char>((value >> 16) & 255),static_cast<unsigned char>((value >> 8) & 255),static_cast<unsigned char>(value & 255) };
		}
		virtual std::array<float, 3> getFloat() const
		{
			auto tmp = getUChar();
			return { (float)tmp[0] / 255.0f,(float)tmp[1] / 255.0f,(float)tmp[1] / 255.0f };
		}
	};

	class s4ColorF : public s4ColorBase
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4ColorF, s4ColorBase>();
	public:
		std::array<float, 3> value;
		s4ColorF(float _r, float _g, float _b)
			:value{_r, _g, _b}
		{}
		s4ColorF(const std::array<float, 3>& _col)
			:s4ColorF(_col[0], _col[1], _col[2])
		{}
		s4ColorF(const s4ColorBase& _col)
			:s4ColorF(_col.getFloat())
		{}

		virtual unsigned int getUInt() const
		{
			return s4Color(this->getUChar()).getUInt();
		}
		virtual std::array<unsigned char, 3> getUChar() const
		{
			return { (unsigned char)(value[0] * 255.0f),(unsigned char)(value[1] * 255.0f),(unsigned char)(value[2] * 255.0f) };
		}
		virtual std::array<float, 3> getFloat() const
		{
			return value;
		}
	};

	class s4ColorHSV : public s4ColorBase
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4ColorHSV, s4ColorBase>();
	public:
		std::array<float, 3> value;
		s4ColorHSV(float _h, float _s, float _v)
			:value{ _h, _s, _v }
		{}
		s4ColorHSV(const std::array<float, 3>& _hsv)
			:s4ColorHSV(_hsv[0], _hsv[1], _hsv[2])
		{}
		s4ColorHSV(const s4ColorBase& _col)
			:value{}
		{
			auto tmp = _col.getFloat();

			auto max_v = (std::max)({ tmp[0],tmp[1],tmp[2] });
			auto min_v = (std::min)({ tmp[0],tmp[1],tmp[2] });

			value[0] = max_v - min_v;

			if (value[0] > 0.0f) {
				if (max_v == tmp[0]) {
					value[0] = (tmp[1] - tmp[2]) / value[0];
					if (value[0] < 0.0f) {
						value[0] += 6.0f;
					}
				}
				else if (max_v == tmp[1]) {
					value[0] = 2.0f + (tmp[2] - tmp[0]) / value[0];
				}
				else {
					value[0] = 4.0f + (tmp[0] - tmp[1]) / value[0];
				}
			}
			value[0] /= 6.0f;
			value[1] = (max_v - min_v);
			if (max_v != 0.0f)
				value[1] /= max_v;
			value[2] = max_v;
		}

		virtual unsigned int getUInt() const
		{
			return s4ColorF(this->getFloat()).getUInt();
		}
		virtual std::array<unsigned char, 3> getUChar() const
		{
			return s4ColorF(this->getFloat()).getUChar();
		}
		virtual std::array<float, 3> getFloat() const
		{
			float r = value[2];
			float g = value[2];
			float b = value[2];
			if (value[1] > 0.0f) {
				const int i = (int)(value[0] * 6);
				const float f = value[0] * 6.0f - (float)i;
				switch (i) {
				default:
				case 0:
					g *= 1 - value[1] * (1 - f);
					b *= 1 - value[1];
					break;
				case 1:
					r *= 1 - value[1] * f;
					b *= 1 - value[1];
					break;
				case 2:
					r *= 1 - value[1];
					b *= 1 - value[1] * (1 - f);
					break;
				case 3:
					r *= 1 - value[1];
					g *= 1 - value[1] * f;
					break;
				case 4:
					r *= 1 - value[1] * (1 - f);
					g *= 1 - value[1];
					break;
				case 5:
					g *= 1 - value[1];
					b *= 1 - value[1] * f;
					break;
				}
			}
			return { r,g,b };
		}
	};
}

#endif // !_GAME2D_S4COLOR_H_
