#ifndef PREPROCESSOR_TEXTDOCUMENT_H
#define PREPROCESSOR_TEXTDOCUMENT_H

#include <algorithm>
#include <fstream>
#include <vector>

#include "Preprocessor.h"
#include "../MetricObject/TextDocument.h"
#include "../Common/util.h"

using namespace std;

namespace jvr
{
	class PreprocessorTextDocument: public Preprocessor<TextDocument>
	{
	private:
		vector<string> stopwords;		//Vector que contiene los stop words que se deben quitar
	public:
		PreprocessorTextDocument()
		{
			ifstream file("stopwords.txt");
			string word;
			
			while (file>>word)
			{
				stopwords.push_back(word);
			}

			file.close();
        	}

        	void preprocess(TextDocument* document)
        	{
            		// Remove all stop words in the file
            		for(auto stopword : stopwords)
            		{
                		auto entry = document->getWords().find(stopword);
				if (entry != document->getWords().end())
					document->getWords().erase(entry);
            		}

			// Clean and Stemming
			map<string, int> temporalWords = document->getWords();
			document->getWords().clear();
			string str;

			for (auto it : temporalWords)
			{
				str = cleanAndApplyStemming(it.first);
				auto itWord = document->getWords().find(str);
				if (itWord == document->getWords().end())
					document->getWords()[str] = it.second;
				else
					itWord->second += it.second;
			}
        	}
	};
}

#endif // PREPROCESSOR_TEXTDOCUMENT_H
