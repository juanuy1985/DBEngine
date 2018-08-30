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
		stemming::spanish_stem<> stemSpanish;		//este objeto aplica stemming en español
		std::wstring wstr = StringToWString(str);
		stemSpanish(wstr);
		std::string strValue = WStringToString(wstr);
		std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::tolower);

		for (char c : charsForRemoving)
		{
			str.erase(std::remove(strValue.begin(), strValue.end(), c), strValue.end());
		}

		return strValue;
	}
}

#endif