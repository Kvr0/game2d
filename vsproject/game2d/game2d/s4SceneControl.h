#pragma once
#ifndef _GAME2D_S4SCENECONTROL_H_
#define _GAME2D_S4SCENECONTROL_H_
#include "s4BaseObject.h"
#include <map>

namespace game2d
{
	template<typename Global>
	class s4Scene : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Scene<Global>, s4BaseObject>();
	public:
		s4Scene() {}
		// 処理実行
		virtual void execute(Global& _gvalue) {}
	};

	template<typename Global>
	class s4SceneController : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Scene<Global>, s4BaseObject>();
		size_t m_scene_id;
		std::map<size_t, s4Scene<Global>*> m_scenes;
	public:
		s4SceneController() :m_scene_id(0u) {}

		// シーン追加
		size_t add(s4Scene<Global>* _scene)
		{
			m_scene_id++;
			m_scenes[m_scene_id] = _scene;
			return m_scene_id;
		}
		// シーン削除
		void remove(size_t _id)
		{
			m_scenes.erase(_id);
		}
		// シーン所持確認
		bool contain(size_t _id)
		{
			return m_scenes.find(_id) != m_scenes.end();
		}

		// シーン取得
		const s4Scene<Global>* get(size_t _id) const
		{
			return m_scenes.at(_id).second;
		}
		s4Scene<Global>* get(size_t _id)
		{
			return m_scenes.at(_id).second;
		}

		// シーン処理実行
		void execute(size_t _id, Global& _gvalue)
		{
			auto it = m_scenes.find(_id);
			if (it != m_scenes.end() && it->second)
			{
				it->second->execute(_gvalue);
			}
		}
	};
}

#endif // !_GAME2D_S4SCENECONTROL_H_
