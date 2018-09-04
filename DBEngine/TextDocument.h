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
            ifstream file(filePath);
            string word;

<<<<<<< HEAD
            while(file>>word)
=======
<<<<<<< HEAD
            while(file>>word)
=======
			while(file>>word)
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
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
