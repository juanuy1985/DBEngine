#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <map>
#include <set>

#include "Index.h"
#include "TextDocument.h"
#include "PreprocessorTextDocument.h"
#include "FeatureExtractorTextDocument.h"

using namespace std;

namespace jvr
{
	class InvertedIndex : public Index< map<string, int>, TextDocument>
	{
	private:
		map<string, set<TextDocument*>> structure;
	public:
		InvertedIndex(PreprocessorTextDocument* preprocessor, FeatureExtractorTextDocument* featureExtractor) :Index(preprocessor, featureExtractor)
		{

		}

		void indexObject( TextDocument* document, map<string, int>* features )
		{
			for (auto pair : *features)
			{
				auto entry = structure.find(pair.first);
				if (entry == structure.end())
				{
					structure[pair.first] = set<TextDocument*>();
				}

				structure[pair.first].insert(document);
			}
		}

		set<TextDocument*> query(string query)
		{
			auto result = structure.find(query);
			if (result == structure.end())
				return set<TextDocument*>();
			return result->second;
		}
	};
}

#endif