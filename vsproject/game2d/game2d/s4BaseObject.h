#pragma once
#ifndef _GAME2D_S4BASEOBJECT_H_
#define _GAME2D_S4BASEOBJECT_H_
#include <map>
#include <list>
#include <set>
#include <typeindex>
namespace game2d
{
	class s4BaseObject
	{
	public:
		// ÉäÉ\Å[ÉXâï˙ã@î\
		class TrashCan
		{
		private:
			class Releaser
			{
			public:
				Releaser() {}
				~Releaser() { TrashCan::release(true); }
			};
		private:
			static inline std::list<std::set<std::pair<s4BaseObject*, bool>>> __objs;
			static inline Releaser __releaser;
		public:
			static void add(s4BaseObject* _obj, bool _array) { if (__objs.empty()) push(); __objs.back().insert({_obj, _array}); }
			static void remove(s4BaseObject* _obj, bool _array) { if (__objs.empty()) return; __objs.back().erase({ _obj, _array}); }
			static void push() { __objs.push_back({}); }
			static void pop() { release(false); }
			static void release(bool _all = false)
			{
				if (__objs.empty()) return;
				auto& last = __objs.back();
				for (auto rit = last.rbegin(); rit != last.rend();)
				{
					auto tmp = *rit;
					last.erase((++rit).base());
					if(tmp.second) delete[] tmp.first;
					else delete tmp.first;
					if (last.empty()) break;
				}
				__objs.pop_back();
				if (_all) release(true);
			}
		};
	public:
		s4BaseObject() {}
		virtual ~s4BaseObject() {}

		// å^åpè≥èÓïÒÇÃìoò^
	private:
		static inline std::map<std::type_index, std::set<std::type_index>> __typeinfo;
	public:
		template<typename Self>
		static bool apply()
		{
			__typeinfo.try_emplace(typeid(Self)).second;
			return true;
		}
		template<typename Self, typename Parent>
		static bool apply()
		{
			std::type_index self = typeid(Self);
			std::type_index parent = typeid(Parent);
			// Parent
			auto it = __typeinfo.try_emplace(self, std::set<std::type_index>()).first;
			it->second.insert(parent);
			return true;
		}
		template<typename Self, typename Parent0, typename Parent1, typename ...Parents>
		static bool apply()
		{
			apply<Self, Parent0>();
			apply<Self, Parent1, Parents...>();
			return true;
		}

		// å^èÓïÒÇÃàÍív
	public:
		static bool isSameAs(const s4BaseObject* _a, const s4BaseObject* _b)
		{
			if (_a == nullptr || _b == nullptr) return _a == nullptr && _b == nullptr;
			return typeid(*_a) == typeid(*_b);
		}

		// å^åpè≥èÓïÒÇÃåüçı
	private:
		static bool isParentOf(const std::type_index& _parent, const std::type_index& _child)
		{
			auto it = __typeinfo.find(_child);
			if (it == __typeinfo.end()) return false;
			// àÍívîªíË
			if (it->first == _parent) return true;
			for (auto& p : it->second)
			{
				// çƒãAåüçı
				if (isParentOf(p, _child)) return true;
			}
			return false;
		}
	public:
		static bool isParentOf(const s4BaseObject* _parent, const s4BaseObject* _child)
		{
			if (_parent == nullptr || _child == nullptr) return false;
			return isParentOf(typeid(*_parent), typeid(*_child));
		}
		template<typename Parent>
		static bool isParentOf(const s4BaseObject* _child)
		{
			if (_child == nullptr) return false;
			return isParentOf(typeid(Parent), typeid(*_child));
		}
		template<typename Child>
		static bool isChildOf(const s4BaseObject* _parent)
		{
			if (_parent == nullptr) return false;
			return isParentOf(typeid(*_parent), typeid(Child));
		}

		// New/Delete
	public:
		static void* operator new(std::size_t _sz)
		{
			auto tmp = ::operator new(_sz, std::nothrow); TrashCan::add((s4BaseObject*)tmp, false); return tmp;
		}
		static void* operator new[](std::size_t _sz)
		{
			auto tmp = ::operator new(_sz, std::nothrow); TrashCan::add((s4BaseObject*)tmp, true); return tmp;
		}
		static void operator delete(void* _p)
		{
			TrashCan::remove((s4BaseObject*)_p, false); ::operator delete(_p, std::nothrow);
		}
		static void operator delete[](void* _p)
		{
			TrashCan::remove((s4BaseObject*)_p, true); ::operator delete(_p, std::nothrow);
		}
	};
}
#endif // !_GAME2D_BASEOBJECT_H_