#pragma once
#ifndef _GAME2D_S4STRING_H_
#define _GAME2D_S4STRING_H_
#include "s4BaseObject.h"
#include <string>
namespace game2d
{
#ifdef UNICODE
	using tstring = std::wstring;
	using tchar = wchar_t;
#else
	using tstring = std::string;
	using tchar = char;
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
}

game2d::s4String operator""_s(const game2d::tchar* _str, std::size_t _count)
{
	return game2d::s4String(_str, _count);
}


#endif // !_GAME2D_S4STRING_H_
