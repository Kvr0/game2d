#pragma once
#ifndef _GAME2D_S4BASEOBJECT_H_
#define _GAME2D_S4BASEOBJECT_H_
#include <map>
#include <set>
#include <typeindex>
namespace game2d
{
	class s4BaseObject
	{
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
	};
}
#endif // !_GAME2D_BASEOBJECT_H_