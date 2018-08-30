#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "stemming\stemming\spanish_stem.h"
#include "stemming\indexing\string_util.h"

using namespace std;

namespace jvr
{
	string charsForRemoving = ".,;:-_+?=)(/*%$#@\"'^~|°<>[]{}¨";

	inline string cleanAndApplyStemming(const string& str)
	{
		string strValue = str;

		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'Á'; }, 'a');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'É'; }, 'e');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'Í'; }, 'i');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'Ó'; }, 'o');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'Ú'; }, 'u');

		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'á'; }, 'a');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'é'; }, 'e');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'í'; }, 'i');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'ó'; }, 'o');
		replace_if(strValue.begin(), strValue.end(), [=](char c) -> bool { return c == 'ú'; }, 'u');

		//remove the chars that are not letters
		for (char c : charsForRemoving)
			strValue.resize(remove_if(strValue.begin(), strValue.end(), [](char x){return !isalnum(x) && !isspace(x); }) - strValue.begin());

		stemming::spanish_stem<> stemSpanish;		//este objeto aplica stemming en español
		std::wstring wstr = StringToWString(strValue);
		stemSpanish(wstr);
		strValue = WStringToString(wstr);
		std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::tolower);

		return strValue;
	}
}

#endif