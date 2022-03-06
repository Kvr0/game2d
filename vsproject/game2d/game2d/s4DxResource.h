#pragma once
#ifndef _GAME2D_S4DXGRAPH_H_
#define _GAME2D_S4DXGRAPH_H_
#include "s4BaseObject.h"
#include "s4String.h"
#include "s4DxLib.h"
#include "s4MathMatrix.h"
#include <vector>

namespace game2d
{
	// リソース
	class s4DxResource : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxResource, s4BaseObject>();
	private:
		bool m_async_f;
	public:
		s4DxResource() :m_async_f(isUsingASync()) {}

		void setASync() { m_async_f = isUsingASync(); }
		bool isASync() const { return m_async_f; }

		virtual bool isLoaded() const = 0;
		virtual void release() = 0;

	private:
		static inline bool __async = false;
	public:
		static bool isUsingASync() { return __async; }
		static void useASync(bool _use = true)
		{
			__async = _use;
			DxLib::SetUseASyncLoadFlag(_use ? TRUE : FALSE);
		}
	};

	// 画像ファイル
	class s4DxGraph : public s4DxResource
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxGraph, s4DxResource>();
	protected:
		int m_handle;
	public:
		s4DxGraph(int _handle) :m_handle(_handle) {}

		int getHandle() const { return m_handle; }
		
		virtual bool load(const s4String& _path)
		{
			m_handle = DxLib::LoadGraph(_path.c_str());
			setASync();
			return m_handle != -1 || isASync();
		}
		virtual bool isLoaded() const
		{
			return CheckHandleASyncLoad(m_handle) == TRUE;
		}
		virtual void release()
		{
			DxLib::DeleteGraph(m_handle);
			m_handle = NULL;
		}
	};

	// 分割画像ファイル
	class s4DxDivGraph : public s4DxResource
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxDivGraph, s4DxResource>();
	protected:
		std::vector<int> m_handle;
	public:
		s4DxDivGraph(const std::vector<int>& _handle) :m_handle(_handle) {}

		const std::vector<int>& getHandle() const { return m_handle; }

		virtual bool load(const s4String& _path, int _allnum, const s4MathVector<int,2>& _num, const s4MathVector<int, 2>& _size)
		{
			int* buffer = new int[_allnum];
			auto result =  DxLib::LoadDivGraph(_path.c_str(),_allnum,_num[0],_num[1],_size[0],_size[1], buffer);
			for (int i = 0; i < _allnum; i++) m_handle.push_back(buffer[i]);
			delete[] buffer;
			setASync();
			return result != -1 || isASync();
		}
		virtual bool isLoaded() const
		{
			bool remaining = false;
			for (auto h : m_handle)
			{
				remaining |= CheckHandleASyncLoad(h) == FALSE;
				if (remaining) break;
			}
			return !remaining;
		}
		virtual void release()
		{
			if(!m_handle.empty()) DxLib::DeleteSharingGraph(m_handle[0]);
			for (auto& h : m_handle) h = NULL;
		}
	};

	// フォントファイル
	class s4DxFont : public s4DxResource
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxFont, s4DxResource>();
	protected:
		int m_handle;
	public:
		s4DxFont(int _handle) :m_handle(_handle) {}

		int getHandle() const { return m_handle; }

		virtual bool load(const s4String& _font, int _size = -1, int _thick = -1, int _type = -1, int _charset = -1, int _edgesize = -1, int _italic = 0)
		{
			m_handle = DxLib::CreateFontToHandle(_font.c_str(), _size, _thick, _type, _charset, _edgesize, _italic);
			setASync();
			return m_handle != -1 || isASync();
		}
		virtual bool isLoaded() const
		{
			return CheckHandleASyncLoad(m_handle) == TRUE;
		}
		virtual void release()
		{
			DxLib::DeleteFontToHandle(m_handle);
			m_handle = NULL;
		}
	};

	// サウンドファイル
	class s4DxSound : public s4DxResource
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4DxSound, s4DxResource>();
	protected:
		int m_handle;
	public:
		s4DxSound(int _handle) :m_handle(_handle) {}

		int getHandle() const { return m_handle; }

		virtual bool load(const s4String& _font, int _size = -1, int _thick = -1, int _type = -1, int _charset = -1, int _edgesize = -1, int _italic = 0)
		{
			m_handle = DxLib::LoadSoundMem(_font.c_str());
			setASync();
			return m_handle != -1 || isASync();
		}
		virtual bool isLoaded() const
		{
			return CheckHandleASyncLoad(m_handle) == TRUE;
		}
		virtual void release()
		{
			DxLib::DeleteSoundMem(m_handle);
			m_handle = NULL;
		}
	};
}

#endif // !_GAME2D_S4DXGRAPH_H_