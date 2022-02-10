#pragma once
#include "BaseObject.h"
namespace game2d
{
#ifdef UNICODE
	using tstring = std::wstring;
	using tchar = wchar_t;
#else
	using tstring = std::string;
	using tchar = char;
#endif

	class String : public BaseObject, public tstring
	{
	private:
		// ObjectType“o˜^—p‰¼•Ï”
		static bool ___;
	public:
		tstring str;

		String(const tchar* _str);
		String(const tchar* _str, std::size_t _count);
		String(const tstring& _str);
	};

	// ƒŠƒeƒ‰ƒ‹‰‰Zq
	extern String operator""_s(const tchar * _str, std::size_t _count);
}