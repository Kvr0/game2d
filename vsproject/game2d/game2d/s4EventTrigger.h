#pragma once
#ifndef _GAME2D_S4EVENTTRIGGER_H_
#define _GAME2D_S4EVENTTRIGGER_H_
#include "s4BaseObject.h"

namespace game2d
{
	class s4Event : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4Event, s4BaseObject>();
	public:
		class EventGroup : public s4BaseObject
		{
		private:
			static inline bool ___ = s4BaseObject::apply<s4Event::EventGroup, s4BaseObject>();
			static inline size_t __id = 0u;
		protected:
			static constexpr size_t provide() { return __id++; }
		private:
			size_t m_id;
		public:
			EventGroup(size_t _id) :m_id(_id) {}

			bool operator==(const EventGroup& _o) const { return m_id == _o.m_id; }
			bool operator<(const EventGroup& _o) const { return m_id < _o.m_id; }
		};

		class EventType : public s4BaseObject
		{
		private:
			static inline bool ___ = s4BaseObject::apply<s4Event::EventType, s4BaseObject>();
			static inline size_t __id = 0u;
		protected:
			static size_t provide() { return __id++; }
		private:
			size_t m_id;
		public:
			EventType(size_t _id) :m_id(_id) {}

			bool operator==(const EventType& _o) const { return m_id == _o.m_id; }
			bool operator<(const EventType& _o) const { return m_id < _o.m_id; }
		};

	public:
		EventGroup egroup;
		EventType etype;

		s4Event(EventGroup _egroup, EventType _etype) :egroup(_egroup), etype(_etype) {}
	};

	class s4MultiEventHandler;

	class s4EventHandler : public s4BaseObject
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4EventHandler, s4BaseObject>();
	public:
		s4EventHandler() {}

		virtual void handle(const s4Event& _event) {}
		void operator()(const s4Event& _event) { handle(_event); }
	};

	class s4MultiEventHandler : public s4EventHandler
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4MultiEventHandler, s4BaseObject>();
	public:

	};
}

#endif // !_GAME2D_S4EVENTTRIGGER_H_