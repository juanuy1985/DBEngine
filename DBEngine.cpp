#include "Preprocessor/PreprocessorTextDocument.h"
#include "FeatureExtractor/FeatureExtractorTextDocument.h"
#include "Index/InvertedIndex.h"
#include "Common/util.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace jvr;


void getInputFiles(vector<string>& files)
{
	ifstream file("/home/ubuntu/Proyectos/DBEngine/Resources/input.txt");
	string filePath;

	while (std::getline(file, filePath))
	{
		files.push_back("/home/ubuntu/Proyectos/DBEngine/Resources/Files/txt/" + filePath);
	}

	file.close();
}

int main()
{
	vector<string> files;
	getInputFiles(files);
	
	PreprocessorTextDocument preprocessor;
	FeatureExtractorTextDocument extractor;
	InvertedIndex index(&preprocessor, &extractor);

	for (string file : files)
	{
		cout<<file.c_str()<<endl;
		index.add(new TextDocument(file.c_str()));
	}

	cout<< endl << "Indice creado con: "<<files.size()<<" documentos."<<endl;

	string str = "";

	cout << endl << "Ingrese palabra a buscar, para salir ingrese -q: ";

	cin >> str;

	while (str != "-q")
	{
		for (auto entry : index.query(cleanAndApplyStemming(str)))
		{
			cout << entry->getFileName() << endl;
		}
		
		cout << endl << "Ingrese palabra a buscar, para salir ingrese -q: ";

		cin >> str;
	}
	cin.get();
	return 0;
}

