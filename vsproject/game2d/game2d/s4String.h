#pragma once
#ifndef _GAME2D_S4STRING_H_
#define _GAME2D_S4STRING_H_
#include "s4BaseObject.h"
#include <string>
#include <sstream>
namespace game2d
{
#ifdef UNICODE
	using tstring = std::wstring;
	using tchar = wchar_t;
	using tstringstream = std::wstringstream;
	using tistream = std::wistream;
	using tostream = std::wostream;
#define TC(x)		L ## x
#else
	using tstring = std::string;
	using tchar = char;
	using tstringstream = std::stringstream;
	using tistream = std::istream;
	using tostream = std::ostream;
#define TC(x)		x
#endif // UNICODE

	class s4String : public s4BaseObject, public tstring
	{
	private:
		static inline bool ___ = s4BaseObject::apply<s4String, s4BaseObject, tstring>();
	public:
		using tstring::tstring;
		s4String(const tstring& _str)
			:tstring(_str) {}
	};

#ifdef UNICODE
#define TSTR(x)      game2d::s4String(L ## x)
#else
#define TSTR(x)      game2d::s4String(x)
#endif // UNICODE


	template <typename T, typename = void>
	struct has_output_operator : std::false_type {};

	template <typename T>
	struct has_output_operator<T, std::void_t<decltype(std::declval<tostream&>() << std::declval<T>())>> : std::true_type {};

	// ílÇÃèoóÕ
	template<typename T>
	auto to_s(tostream& _os, const T& _v)
		-> std::enable_if_t<has_output_operator<T>::value>
	{
		_os << _v;
	}
	template<typename T>
	auto to_s(tostream& _os, const T& _v)
		-> std::enable_if_t<!has_output_operator<T>::value>
	{
		_os << "[" << typeid(_v).name() << "]";
	}

	// ï∂éöóÒïœä∑ (Stream)
	template<typename Head>
	void toString_s(tostream& _os, const Head& _v0)
	{
		to_s(_os, _v0);
	}
	template<typename Head, typename ...Tail>
	void toString_s(tostream& _os, const Head& _v0, const Tail&... tails)
	{
		to_s(_os, _v0);
		_os << TC(", ");
		toString_s(_os, tails...);
	}

	// ï∂éöóÒïœä∑
	template<typename Head, typename ...Tail>
	s4String toString(const Head& _v0, const Tail&... tails)
	{
		tstringstream ss;
		toString_s(ss, _v0, tails...);
		return ss.str();
	}
	template<typename Head>
	s4String toString(const Head& _v0)
	{
		tstringstream ss;
		toString_s(ss, _v0);
		return ss.str();
	}
}

game2d::s4String operator""_s(const game2d::tchar* _str, std::size_t _count)
{
	return game2d::s4String(_str, _count);
}

#endif // !_GAME2D_S4STRING_H_
