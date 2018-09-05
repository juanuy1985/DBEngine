<<<<<<< HEAD
#ifndef PREPROCESSOR_TEXTDOCUMENT_H
#define PREPROCESSOR_TEXTDOCUMENT_H

=======
<<<<<<< HEAD
#ifndef PREPROCESSOR_TEXTDOCUMENT_H
#define PREPROCESSOR_TEXTDOCUMENT_H

=======
#pragma once

#ifndef PREPROCESSOR_TEXTDOCUMENT_H
#define PREPROCESSOR_TEXTDOCUMENT_H

#include <algorithm>
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
#include <fstream>
#include <vector>

#include "Preprocessor.h"
#include "TextDocument.h"
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include "util.h"
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine

using namespace std;

namespace jvr
{
    class PreprocessorTextDocument: public Preprocessor<TextDocument>
    {
    private:
<<<<<<< HEAD
        vector<string> stopwords;
=======
<<<<<<< HEAD
        vector<string> stopwords;
=======
        vector<string> stopwords;					//Vector que contiene los stop words que se deben quitar
		
	private:

>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
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
            //Remove all stop words in the file
            for(auto stopword : stopwords)
            {
                auto entry = document->getWords().find(stopword);
				if (entry != document->getWords().end())
					document->getWords().erase(entry);
            }

<<<<<<< HEAD
            //Stemming

=======
<<<<<<< HEAD
            //Stemming

=======
			//Apply Stemming
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
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
        }
    };
}

#endif // PREPROCESSOR_TEXTDOCUMENT_H
