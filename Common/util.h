#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "stemming/stemming/spanish_stem.h"
#include "stemming/indexing/string_util.h"

using namespace std;

namespace jvr
{
	string charsForRemoving = ".,;:-_+?=)(/*%$#@\"'^~|�<>[]{}�";

	inline string cleanAndApplyStemming(const string& str)
	{
		string strValue = str;

		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'a');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'e');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'i');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'o');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'u');

		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'a');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'e');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'i');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'o');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == '�'; }, 'u');

		//remove the chars that are not letters
		for (char c : charsForRemoving)
			strValue.resize(remove_if(strValue.begin(), strValue.end(), [](char x){return !isalnum(x) && !isspace(x); }) - strValue.begin());

		stemming::spanish_stem<> stemSpanish;		//este objeto aplica stemming en espa�ol
		std::wstring wstr = StringToWString(strValue);
		stemSpanish(wstr);
		strValue = WStringToString(wstr);
		std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::tolower);

		return strValue;
	}
}

#endif
