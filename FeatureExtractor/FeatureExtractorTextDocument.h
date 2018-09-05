#ifndef FEATURE_EXTRACTOR_TEXTDOCUMENT_H
#define FEATURE_EXTRACTOR_TEXTDOCUMENT_H

#include <map>

#include "FeatureExtractor.h"
#include "TextDocument.h"

using namespace std;

namespace jvr
{
	class FeatureExtractorTextDocument: public FeatureExtractor< map<string, int>, TextDocument >
	{
	public:
		map<string, int>* getFeatures(TextDocument* object)
		{
			return &object->getWords();
		}
	};
}

#endif