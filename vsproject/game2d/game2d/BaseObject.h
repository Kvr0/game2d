#pragma once

namespace game2d
{
	// Šî’êƒIƒuƒWƒFƒNƒgƒNƒ‰ƒX
	class BaseObject
	{
	public:
		BaseObject() {}
		virtual ~BaseObject() {}
	};

	// Œ^Œp³î•ñƒNƒ‰ƒX
	class ObjectType
	{
	public:
		// ©g‚Ìî•ñ
		std::type_index self;
		// Œp³eî•ñ
		std::set<std::type_index> parent;
		// Œp³qî•ñ
		std::set<std::type_index> child;

	public:
		ObjectType(const std::type_index& _index) :self(_index) {}
		// Œp³e’Ç‰Á
		void addParent(const std::type_index& _index)
		{
			parent.insert(_index);
		}
		// Œp³q’Ç‰Á
		void addChild(const std::type_index& _index)
		{
			child.insert(_index);
		}
	private:
		// ŠÇ——p
		static std::map<std::type_index, ObjectType> m_objectTypes;
	protected:
		// Œ^Œp³î•ñ‚Ì’Ç‰Á (Œp³‚È‚µ)
		static bool add(const std::type_index& _index)
		{
			return m_objectTypes.try_emplace(_index, ObjectType(_index)).second;
		}
		// Œ^Œp³î•ñ‚Ì’Ç‰Á (Œp³‚ ‚è)
		static bool add(const std::type_index& _index, const std::type_index& _parent)
		{
			auto ret0 = m_objectTypes.try_emplace(_index, ObjectType(_index));
			if (ret0.first != m_objectTypes.end())
			{
				ret0.first->second.addParent(_parent);
			}
			auto ret1 = m_objectTypes.try_emplace(_parent, ObjectType(_parent));
			if (ret1.first != m_objectTypes.end())
			{
				ret1.first->second.addChild(_index);
			}
			return ret0.second;
		}
	public:
		// Œ^Œp³î•ñ‚Ì“o˜^ (Œp³‚È‚µ)
		template<typename Self>
		static bool add()
		{
			return add(typeid(Self));
		}
		// Œ^Œp³î•ñ‚Ì“o˜^ (Œp³‚ ‚è)
		template<typename Self, typename Parent0>
		static bool add()
		{
			bool tmp = false;
			tmp |= add<Self>();
			tmp |= add(typeid(Self), typeid(Parent0));
			return tmp;
		}
		// Œ^Œp³î•ñ‚Ì“o˜^ (‘½dŒp³)
		template<typename Self, typename Parent0, typename Parent1, typename ...Parents>
		static bool add()
		{
			bool tmp = false;
			tmp |= add<Self, Parent0>();
			tmp |= add<Self, Parent1, Parents...>();
			return tmp;
		}

		// Œ^Œp³î•ñ‚Ìæ“¾
		template<typename Self>
		static const ObjectType& get()
		{
			m_objectTypes.try_emplace(typeid(Self), ObjectType(typeid(Self)));
			return m_objectTypes.at(typeid(Self));
		}

		static const ObjectType& get(const std::type_index& _a)
		{
			return m_objectTypes.try_emplace(_a, ObjectType(_a)).first->second;
		}
		static const ObjectType& get(const BaseObject* _a)
		{
			return get(typeid(_a));
		}

		// ‚·‚×‚Ä‚ÌŒ^Œp³î•ñ‚Ìæ“¾
		static const std::map<std::type_index, ObjectType>& get()
		{
			return m_objectTypes;
		}

		// Œ^î•ñ‚Ìˆê’v”äŠr
		static bool isSame(const BaseObject* _a, const BaseObject* _b)
		{
			return typeid(*_a) == typeid(*_b);
		}

		// Œ^î•ñ‚ÌŒp³e”»’è
		static bool isParent(const std::type_index& _target, const std::type_index& _parent)
		{
			if (get(_target).self == get(_parent).self) return true;
			auto& tmp = get(_parent);
			for (auto& c : tmp.parent) if (isParent(_target, c)) return true;
			return false;
		}
		static bool isParent(const BaseObject* _target, const BaseObject* _parent)
		{
			return isParent(typeid(*_target), typeid(*_parent));
		}
		template<typename P>
		bool isParent(const BaseObject* _target) const
		{
			return isParent(typeid(*_target), typeid(P));
		}

		// Œ^î•ñ‚ÌŒp³q”»’è
		static bool isChild(const std::type_index& _target, const std::type_index& _child)
		{
			if (get(_target).self == get(_child).self) return true;
			auto& tmp = get(_child);
			for (auto& c : tmp.child) if (isChild(_target, c)) return true;
			return false;
		}
		static bool isChild(const BaseObject* _target, const BaseObject* _child)
		{
			return isChild(typeid(*_target), typeid(*_child));
		}
		template<typename C>
		bool isChild(const BaseObject* _target) const
		{
			return isChild(typeid(*_target), typeid(C));
		}
	};
}