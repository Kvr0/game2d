#pragma once
#ifndef _GAME2D_S4DXPRIMITIVE_H_
#define _GAME2D_S4DXPRIMITIVE_H_
#include "s4BaseObject.h"
#include "s4DxRender.h"
#include <vector>

namespace game2d
{
	// 頂点情報
	class s4DxVertex : public s4BaseObject, public DxLib::VERTEX2D
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxVertex, s4BaseObject>();
	public:
		s4DxVertex(const s4PositionF& _pos, const s4Color& _dif, const s4PositionF& _uv = {0.0f, 0.0f})
		{
			this->pos.x = _pos[0];
			this->pos.y = _pos[1];
			this->pos.z = 0.0f;
			this->rhw = 1.0f;
			auto col_buf = _dif.getUChar();
			this->dif.r = col_buf[0];
			this->dif.g = col_buf[1];
			this->dif.b = col_buf[2];
			this->dif.a = col_buf[3];
			this->u = _uv[0];
			this->v = _uv[1];
		}
	};

	// プリミティブ
	class s4DxPrimitive : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxPrimitive, s4BaseObject>();
	public:
		enum class Type : int
		{
			PointList = DX_PRIMTYPE_POINTLIST,
			LineList = DX_PRIMTYPE_LINELIST,
			LineStrip = DX_PRIMTYPE_LINESTRIP,
			TriangleList = DX_PRIMTYPE_TRIANGLELIST,
			TriangleStrip = DX_PRIMTYPE_TRIANGLESTRIP,
			TriangleFan = DX_PRIMTYPE_TRIANGLEFAN
		};
	public:
		std::vector<VERTEX2D> vertex;
		std::vector<unsigned short> index;
		Type type;

		s4DxPrimitive(const std::vector<s4DxVertex>& _vertex, const std::vector<unsigned short>& _index, Type _type)
			:vertex(_vertex.begin(),_vertex.end()), index(_index), type(_type)
		{
		}
		s4DxPrimitive(const std::vector<s4DxVertex>& _vertex, Type _type)
			:s4DxPrimitive(_vertex, {}, _type)
		{
			for (size_t i = 0; i < vertex.size(); i++)
			{
				index.push_back((unsigned short)i);
			}
		}
		void render(int _ghandle = DX_NONE_GRAPH, bool _trans = true) const
		{
			DxLib::DrawPrimitiveIndexed2D(vertex.data(), (int)vertex.size(), index.data(), (int)index.size(), (int)type, _ghandle, _trans ? TRUE : FALSE);
		}
	};
}

#endif // !_GAME2D_S4DXPRIMITIVE_H_
