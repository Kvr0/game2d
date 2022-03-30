#pragma once
#ifndef _GAME2D_S4EVENTTRIGGER_H_
#define _GAME2D_S4EVENTTRIGGER_H_
#include "s4BaseObject.h"

namespace game2d
{
	// イベント
	class s4Event : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Event, s4BaseObject>();
	public:
		// イベントグループ
		class Group : public s4BaseObject
		{
		private:
			static inline bool ___ = s4BaseObject::apply<s4Event::Group, s4BaseObject>();
			static inline size_t __id = 0u;
		public:
			// 新規グループIDの提供
			static constexpr size_t provide() { return __id++; }
		public:
			// イベントタイプ
			class Type : public s4BaseObject
			{
			private:
				static inline bool ___ = s4BaseObject::apply<s4Event::Group::Type, s4BaseObject>();
			private:
				size_t m_id;
			public:
				Type(size_t _id) :m_id(_id) {}

				bool operator==(const Type& _o) const { return m_id == _o.m_id; }
				bool operator<(const Type& _o) const { return m_id < _o.m_id; }
			};
		private:
			size_t m_id;
			size_t m_type_id;
		public:
			Group(size_t _id) :m_id(_id), m_type_id(0u) {}

			// 新規Typeの作成
			Type makeType() { return Type(m_type_id++); }

			bool operator==(const Group& _o) const { return m_id == _o.m_id; }
			bool operator<(const Group& _o) const { return m_id < _o.m_id; }
		};

	public:
		Group egroup;
		Group::Type etype;

		s4Event(Group _egroup, Group::Type _etype) :egroup(_egroup), etype(_etype) {}
	};

	namespace s4event
	{
		class s4None : public s4Event
		{
		private:
			static inline bool ___ = s4BaseObject::apply<s4None, s4Event>();
		public:
			static inline s4Event::Group group = s4Event::Group::provide();
			static inline s4Event::Group::Type type = group.makeType();

			s4None() : s4Event(group, type) {}
		};
	}

	class s4EventHandler : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4EventHandler, s4BaseObject>();
	private:
		static inline std::map<s4EventHandler*, std::pair<std::set<s4EventHandler*>,std::list<s4Event*>>> __handler;
		// ハンドラーの追加
		static void add_handler(s4EventHandler& _self, s4EventHandler& _ehandler)
		{
			__handler[&_self].first.insert(&_ehandler);
		}
		static void add_handler(s4EventHandler& _self)
		{
			__handler.try_emplace(&_self);
		}
		// ハンドラーの削除
		static void remove_handler(s4EventHandler& _self, s4EventHandler& _ehandler)
		{
			__handler[&_self].first.erase(&_ehandler);
		}
		static void remove_handler(s4EventHandler& _self)
		{
			__handler.erase(&_self);
		}
		// イベントの受け取り
		static void receive_event(s4EventHandler& _self, const s4Event& _e, s4EventHandler* _root)
		{
			for (auto h : __handler[&_self].first)
			{
				if (h != _root)
				{
					if(auto it = __handler.find(h);it != __handler.end()) h->receiveEvent(_e, _root);
				}
			}
		}
		// スタックの取得
		static const std::list<s4Event*>& get_stack(s4EventHandler& _self)
		{
			return __handler[&_self].second;
		}
		// スタックへの追加
		static void add_stack(s4EventHandler& _self, s4Event* _e)
		{
			__handler[&_self].second.push_back(_e);
		}
		// スタックへの削除
		static void clear_stack(s4EventHandler& _self)
		{
			__handler[&_self].second.clear();
		}
	public:
		s4EventHandler()
		{
			add_handler(*this);
		}
		virtual ~s4EventHandler()
		{
			remove_handler(*this);
		}

		virtual void addHandler(s4EventHandler& _ehandler)
		{
			add_handler(*this, _ehandler);
		}
		virtual void removeHandler(s4EventHandler& _ehandler)
		{
			remove_handler(*this, _ehandler);
		}
		const std::set<s4EventHandler*>& getHandler() const { return __handler[(s4EventHandler*)this].first; }
		std::set<s4EventHandler*>& getHandler() { return __handler[this].first; }

		virtual void receiveEvent(s4Event& _e, s4EventHandler* _root = nullptr)
		{
			receive_event(*this, _e, _root ? _root : this);
		}

		virtual const std::list<s4Event*>& getStack()
		{
			return get_stack(*this);
		}
		virtual void addStack(s4Event* _e)
		{
			add_stack(*this, _e);
		}
		virtual void clearStack()
		{
			clear_stack(*this);
		}
	};
}

#endif // !_GAME2D_S4EVENTTRIGGER_H_