#include "pch.h"
#include "String.h"
namespace game2d
{
	// •¶š—ñƒNƒ‰ƒX
	
	// ObjectType“o˜^—p‰¼•Ï”
	bool String::___ = ObjectType::add<String, BaseObject, tstring>();

	String::String(const tchar* _str)
		:tstring(_str)
	{
	}
	String::String(const tchar* _str, std::size_t _count)
		: tstring(_str)
	{
	}
	String::String(const tstring& _str)
		: tstring(_str)
	{
	}

	// ƒŠƒeƒ‰ƒ‹‰‰Zq
	String operator""_s(const tchar * _str, std::size_t _count)
	{
		return String(_str, _count);
	}
}