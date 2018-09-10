#include "Preprocessor/PreprocessorTextDocument.h"
#include "FeatureExtractor/FeatureExtractorTextDocument.h"
#include "Index/IndexVectorTextDocument.h"
#include "Common/Distances.h"

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
	IndexVectorTextDocument index(&preprocessor, &extractor, EuclideanDistance);

	for (string file : files)
	{
		cout<<file.c_str()<<endl;
		index.add(new TextDocument(file.c_str()));
	}

	cout<< endl << "Indice creado con: "<<files.size()<<" documentos."<<endl;

	string file = "";

	cout << endl << "Ingrese documento a buscar, para salir ingrese -q: ";

	cin >> file;

	while (file != "-q")
	{
		if(fileExists(file))
		{
			cout << "resultado: " << endl;
			TextDocument* document = new TextDocument(file.c_str());
			set<TextDocument*> results = index.query(document);
			for(TextDocument* result : results)
			{
				cout<<result->getFileName()<<endl;
			}
		}
		else
		{
			cout << "archivo: " << file << " no existe." << endl;
		}
		
		cout << endl << "Ingrese palabra a buscar, para salir ingrese -q: ";

		cin >> file;
	}
	cin.get();
	return 0;
}

