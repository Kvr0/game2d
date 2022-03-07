#pragma once
#ifndef _GAME2D_S4DXRENDER_H_
#define _GAME2D_S4DXRENDER_H_
#include "s4DxLib.h"
#include "s4Matrix.h"
#include "s4MathMatrix.h"
#include "s4Color.h"
#include "s4String.h"
#include "s4DxResource.h"
#include <list>
namespace game2d
{
	// ç¿ïWå^
	using s4Position = s4MathVector<int, 2>;
	using s4PositionF = s4MathVector<float, 2>;
	// ïœà å^
	using s4Size = s4Position;
	using s4SizeF = s4PositionF;

	// ê}å`ï`âÊ
	class s4DxRenderShape
	{
	public:
		static void line(const s4Position& _p0, const s4Position& _p1, const s4ColorBase& _col, int _thickness = 1)
		{
			DxLib::DrawLine(_p0[0], _p0[1], _p1[0], _p1[1], _col.getUInt(), _thickness);
		}
		static void box(const s4Position& _p0, const s4Position& _p1, const s4ColorBase& _col, bool _fill)
		{
			DxLib::DrawBox(_p0[0], _p0[1], _p1[0], _p1[1], _col.getUInt(), _fill ? TRUE : FALSE);
		}
		static void circle(const s4Position& _p, int _r, const s4ColorBase& _col, bool _fill, int _thickness = 1)
		{
			DxLib::DrawCircle(_p[0], _p[1], _r, _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void oval(const s4Position& _p, const s4Size& _r, const s4ColorBase& _col, bool _fill, int _thickness = 1)
		{
			DxLib::DrawOval(_p[0], _p[1], _r[0], _r[1], _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void ovalrect(const s4Position& _p0, const s4Position& _p1, const s4ColorBase& _col, bool _fill)
		{
			DxLib::DrawOval_Rect(_p0[0], _p0[1], _p1[0], _p1[1], _col.getUInt(), _fill ? TRUE : FALSE);
		}
		static void triangle(const s4Position& _p0, const s4Position& _p1, const s4Position& _p2, const s4ColorBase& _col, bool _fill)
		{
			DxLib::DrawTriangle(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _col.getUInt(), _fill ? TRUE : FALSE);
		}
		static void quadrangle(const s4Position& _p0, const s4Position& _p1, const s4Position& _p2, const s4Position& _p3, const s4ColorBase& _col, bool _fill)
		{
			DxLib::DrawQuadrangle(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _p3[0], _p3[1], _col.getUInt(), _fill ? TRUE : FALSE);
		}
		static void roundrect(const s4Position& _p0, const s4Position& _p1, const s4Size& _r, const s4ColorBase& _col, bool _fill)
		{
			DxLib::DrawRoundRect(_p0[0], _p0[1], _p1[0], _p1[1], _r[0], _r[1], _col.getUInt(), _fill ? TRUE : FALSE);
		}
		static void pixel(const s4Position& _p, const s4ColorBase& _col)
		{
			DxLib::DrawPixel(_p[0], _p[1], _col.getUInt());
		}
	};
	class s4DxRenderShapeF
	{
	public:
		static void line(const s4PositionF& _p0, const s4PositionF& _p1, const s4ColorBase& _col, float _thickness = 1)
		{
			DxLib::DrawLineAA(_p0[0], _p0[1], _p1[0], _p1[1], _col.getUInt(), _thickness);
		}
		static void box(const s4PositionF& _p0, const s4PositionF& _p1, const s4ColorBase& _col, bool _fill, float _thickness = 1)
		{
			DxLib::DrawBoxAA(_p0[0], _p0[1], _p1[0], _p1[1], _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void circle(const s4PositionF& _p, float _r, const s4ColorBase& _col, bool _fill, int _posnum = 16, float _thickness = 1)
		{
			DxLib::DrawCircleAA(_p[0], _p[1], _r, _posnum, _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void oval(const s4PositionF& _p, const s4SizeF& _r, const s4ColorBase& _col, bool _fill, int _posnum = 16, float _thickness = 1)
		{
			DxLib::DrawOvalAA(_p[0], _p[1], _r[0], _r[1], _posnum, _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void triangle(const s4PositionF& _p0, const s4PositionF& _p1, const s4PositionF& _p2, const s4ColorBase& _col, bool _fill, float _thickness = 1)
		{
			DxLib::DrawTriangleAA(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void quadrangle(const s4PositionF& _p0, const s4PositionF& _p1, const s4PositionF& _p2, const s4PositionF& _p3, const s4ColorBase& _col, bool _fill, float _thickness = 1)
		{
			DxLib::DrawQuadrangleAA(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _p3[0], _p3[1], _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
		static void roundrect(const s4PositionF& _p0, const s4PositionF& _p1, const s4SizeF& _r, const s4ColorBase& _col, bool _fill, int _posnum = 16, float _thickness = 1)
		{
			DxLib::DrawRoundRectAA(_p0[0], _p0[1], _p1[0], _p1[1], _r[0], _r[1], _posnum, _col.getUInt(), _fill ? TRUE : FALSE, _thickness);
		}
	};

	// ï∂éöóÒï`âÊ	
	class s4DxRenderString
	{
	public:
		// ï`âÊ
		static void string(const s4Position& _p, const s4String& _str, size_t _len, const s4ColorBase& _col, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			DxLib::DrawNStringToHandle(_p[0], _p[1], _str.c_str(), _len, _col.getUInt(), _fonthandle, 0u, _vertical ? TRUE : FALSE);
		}
		static void string(const s4Position& _p, const s4String& _str, const s4ColorBase& _col, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			string(_p, _str, strlenDx(_str.c_str()), _col, _vertical, _fonthandle);
		}

		// ï`âÊóÃàÊÉTÉCÉY
		static s4Size getSize(const s4String& _str, size_t _len, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			s4Size tmp;
			DxLib::GetDrawNStringSizeToHandle(&tmp[0], &tmp[1], nullptr, _str.c_str(), _len, _fonthandle, _vertical ? TRUE : FALSE);
			return tmp;
		}
		static s4Size getSize(const s4String& _str, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			return getSize(_str, strlenDx(_str.c_str()), _vertical, _fonthandle);
		}
	};
	class s4DxRenderStringF
	{
	public:
		// ï`âÊ
		static void string(const s4PositionF& _p, const s4String& _str, size_t _len, const s4ColorBase& _col, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			DxLib::DrawNStringFToHandle(_p[0], _p[1], _str.c_str(), _len, _col.getUInt(), _fonthandle, 0u, _vertical ? TRUE : FALSE);
		}
		static void string(const s4PositionF& _p, const s4String& _str, const s4ColorBase& _col, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			string(_p, _str, strlenDx(_str.c_str()), _col, _vertical, _fonthandle);
		}

		// ï`âÊóÃàÊÉTÉCÉY
		static s4SizeF getSize(const s4String& _str, size_t _len, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			s4Size tmp;
			DxLib::GetDrawNStringSizeToHandle(&tmp[0], &tmp[1], nullptr, _str.c_str(), _len, _fonthandle, _vertical ? TRUE : FALSE);
			return { (float)tmp[0],(float)tmp[1] };
		}
		static s4SizeF getSize(const s4String& _str, bool _vertical = false, int _fonthandle = DX_DEFAULT_FONT_HANDLE)
		{
			return getSize(_str, strlenDx(_str.c_str()), _vertical, _fonthandle);
		}
	};

	// âÊëúï`âÊ
	class s4DxRenderGraph
	{
	public:
		static void graph(const s4Position& _p, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawGraph(_p[0], _p[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void extend(const s4Position& _p0, const s4Position& _p1, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawExtendGraph(_p0[0], _p0[1], _p1[0], _p1[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void rota(const s4Position& _p, const s4Position& _c, const s4DxGraph& _graph, const s4Vector<double, 2>& _rate = { 1.0, 1.0 }, double _angle = 0.0, const s4Vector<bool, 2>& _reverse = { false, false }, bool _trans = true)
		{
			DxLib::DrawRotaGraph3(_p[0], _p[1], _c[0], _c[1], _rate[0], _rate[1], _angle, _graph.getHandle(), _trans ? TRUE : FALSE, _reverse[0] ? TRUE : FALSE, _reverse[1] ? TRUE : FALSE);
		}
		static void modi(const s4Position& _p0, const s4Position& _p1, const s4Position& _p2, const s4Position& _p3, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawModiGraph(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _p3[0], _p3[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void reverse(const s4Position& _p, const s4DxGraph& _graph, const s4Vector<bool, 2>& _reverse = { false, false }, bool _trans = true)
		{
			DxLib::DrawReverseGraph(_p[0], _p[1], _graph.getHandle(), _trans ? TRUE : FALSE, _reverse[0] ? TRUE : FALSE, _reverse[1] ? TRUE : FALSE);
		}
	};
	class s4DxRenderGraphF
	{
	public:
		static void graph(const s4PositionF& _p, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawGraphF(_p[0], _p[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void extend(const s4PositionF& _p0, const s4PositionF& _p1, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawExtendGraphF(_p0[0], _p0[1], _p1[0], _p1[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void rota(const s4PositionF& _p, const s4PositionF& _c, const s4DxGraph& _graph, const s4Vector<double, 2>& _rate = { 1.0, 1.0 }, double _angle = 0.0, const s4Vector<bool, 2>& _reverse = { false, false }, bool _trans = true)
		{
			DxLib::DrawRotaGraph3F(_p[0], _p[1], _c[0], _c[1], _rate[0], _rate[1], _angle, _graph.getHandle(), _trans ? TRUE : FALSE, _reverse[0] ? TRUE : FALSE, _reverse[1] ? TRUE : FALSE);
		}
		static void modi(const s4PositionF& _p0, const s4PositionF& _p1, const s4PositionF& _p2, const s4PositionF& _p3, const s4DxGraph& _graph, bool _trans = true)
		{
			DxLib::DrawModiGraphF(_p0[0], _p0[1], _p1[0], _p1[1], _p2[0], _p2[1], _p3[0], _p3[1], _graph.getHandle(), _trans ? TRUE : FALSE);
		}
		static void reverse(const s4PositionF& _p, const s4DxGraph& _graph, const s4Vector<bool, 2>& _reverse = { false, false }, bool _trans = true)
		{
			DxLib::DrawReverseGraphF(_p[0], _p[1], _graph.getHandle(), _trans ? TRUE : FALSE, _reverse[0] ? TRUE : FALSE, _reverse[1] ? TRUE : FALSE);
		}
	};

	// BlendMode
	class s4DxBlendMode
	{
	public:
		enum class Mode : int
		{
			NoBlend = DX_BLENDMODE_NOBLEND,
			Alpha = DX_BLENDMODE_ALPHA,
			Add = DX_BLENDMODE_ADD,
			Sub = DX_BLENDMODE_SUB,
			Mul = DX_BLENDMODE_MUL,
			Sub2 = DX_BLENDMODE_SUB2,
			Xor = DX_BLENDMODE_XOR,
			DestColor = DX_BLENDMODE_DESTCOLOR,
			InvDestColor = DX_BLENDMODE_INVDESTCOLOR,
			InvSrc = DX_BLENDMODE_INVSRC,
			MulA = DX_BLENDMODE_MULA,
			AlphaX4 = DX_BLENDMODE_ALPHA_X4,
			AddX4 = DX_BLENDMODE_ADD_X4,
			SrcColor = DX_BLENDMODE_SRCCOLOR,
			HalfAdd = DX_BLENDMODE_HALF_ADD,
			Sub1 = DX_BLENDMODE_SUB1,
			PmaAlpha = DX_BLENDMODE_PMA_ALPHA,
			PmaAdd = DX_BLENDMODE_PMA_ADD,
			PmaSub = DX_BLENDMODE_PMA_SUB,
			PmaInvSrc = DX_BLENDMODE_PMA_INVSRC,
			PmaAlphaX4 = DX_BLENDMODE_PMA_ALPHA_X4,
			PmaAddX4 = DX_BLENDMODE_PMA_ADD_X4,
			Live2dZero = DX_BLENDMODE_LIVE2D_ZERO,
			Live2dNormal = DX_BLENDMODE_LIVE2D_NORMAL,
			Live2dAdd = DX_BLENDMODE_LIVE2D_ADD,
			Live2dMult = DX_BLENDMODE_LIVE2D_MULT,
			Live2dMask = DX_BLENDMODE_LIVE2D_MASK
		};
	private:
		static inline std::list<std::pair<Mode,int>> __mode = {};
	public:
		// éÊìæ
		static std::pair<Mode, int> get()
		{
			int mode, param;
			DxLib::GetDrawBlendMode(&mode, &param);
			return { (Mode)mode, param };
		}
		// ê›íË
		static void set(Mode _mode, int _param)
		{
			DxLib::SetDrawBlendMode((int)_mode, _param);
		}
		// ï€ë∂
		static void push()
		{
			__mode.push_back(get());
		}
		// ì«Ç›çûÇ›
		static void pop()
		{
			if (!__mode.empty())
			{
				set(__mode.back().first, __mode.back().second);
				__mode.pop_back();
			}
		}
	};
}

#endif // !_GAME2D_S4DXRENDER_H_
