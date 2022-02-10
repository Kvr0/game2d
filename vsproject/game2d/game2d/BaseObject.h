#pragma once

namespace game2d
{
	// 基底オブジェクトクラス
	class BaseObject
	{
	public:
		BaseObject() {}
		virtual ~BaseObject() {}
	};

	// 型継承情報クラス
	class ObjectType
	{
	public:
		// 自身の情報
		std::type_index self;
		// 継承親情報
		std::set<std::type_index> parent;
		// 継承子情報
		std::set<std::type_index> child;

	public:
		ObjectType(const std::type_index& _index) :self(_index) {}
		// 継承親追加
		void addParent(const std::type_index& _index)
		{
			parent.insert(_index);
		}
		// 継承子追加
		void addChild(const std::type_index& _index)
		{
			child.insert(_index);
		}
	private:
		// 管理用
		static std::map<std::type_index, ObjectType> m_objectTypes;
	protected:
		// 型継承情報の追加 (継承なし)
		static void add(const std::type_index& _index)
		{
			m_objectTypes.try_emplace(_index, ObjectType(_index));
		}
		// 型継承情報の追加 (継承あり)
		static void add(const std::type_index& _index, const std::type_index& _parent)
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
		}
	public:
		// 型継承情報の登録 (継承なし)
		template<typename Self>
		static void add()
		{
			add(typeid(Self));
		}
		// 型継承情報の登録 (継承あり)
		template<typename Self, typename Parent0>
		static void add()
		{
			add<Self>();
			add(typeid(Self), typeid(Parent0));
		}
		// 型継承情報の登録 (多重継承)
		template<typename Self, typename Parent0, typename Parent1, typename ...Parents>
		static void add()
		{
			add<Self, Parent0>();
			add<Self, Parent1, Parents...>();
		}

		// 型継承情報の取得
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

		// すべての型継承情報の取得
		static const std::map<std::type_index, ObjectType>& get()
		{
			return m_objectTypes;
		}

		// 型情報の一致比較
		static bool isSame(const BaseObject* _a, const BaseObject* _b)
		{
			return typeid(*_a) == typeid(*_b);
		}

		// 型情報の継承親判定
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

		// 型情報の継承子判定
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