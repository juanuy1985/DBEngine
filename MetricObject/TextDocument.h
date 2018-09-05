#ifndef TEXT_DOCUMENT_H
#define TEXT_DOCUMENT_H

#include <fstream>
#include <string>
#include <map>

using namespace std;

namespace jvr
{
    class TextDocument
    {
    private:
        string filePath;
        map<string, int> words;
    public:
        TextDocument(string filePath)
        {
            this->filePath = filePath;
            loadAllWords();
        }

		map<string, int>& getWords()
		{
			return words;
		}

		string getFileName()
		{
			return filePath;
		}

    protected:
        void loadAllWords()
        {
            words.clear();
            ifstream file(filePath.c_str());
            string word;

	    while(file>>word)
            {
                auto mapEntry = words.find(word);
		if (mapEntry != words.end())
			mapEntry->second++;
		else
			words[word] = 1;
            }

            file.close();
        }
    };
}

#endif // TEXT_DOCUMENT_H
