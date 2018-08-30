// DBEngine.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> Creation of the DBEngine
#include "DBCollection.h"
#include "PreprocessorTextDocument.h"
#include "FeatureExtractorTextDocument.h"
#include "InvertedIndex.h"
<<<<<<< HEAD
=======
=======
#include "PreprocessorTextDocument.h"
#include "FeatureExtractorTextDocument.h"
#include "InvertedIndex.h"
#include "util.h"
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine

#include <iostream>
#include <vector>

using namespace std;
using namespace jvr;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> Creation of the DBEngine
int main()
{
	vector<string> files;
	
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\ciencia_meditacion.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\despertar_hombre.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\educacion_fundamental.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\gran_rebelion.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\introduccion_gnosis.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\mirando_misterio.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\platillos_voladores.txt");
	files.push_back("D:\\Maestria\\Recuperación de la información\\txt\\psicologia_revolucionaria.txt");

<<<<<<< HEAD
=======
=======
void getInputFiles(vector<string>& files)
{
	ifstream file("input.txt");
	string filePath;

	while (std::getline(file, filePath))
	{
		files.push_back(filePath);
	}

	file.close();
}

int main()
{
	vector<string> files;
	getInputFiles(files);
	
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
	PreprocessorTextDocument preprocessor;
	FeatureExtractorTextDocument extractor;
	InvertedIndex index(&preprocessor, &extractor);

	for (string file : files)
	{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> Creation of the DBEngine
		index.add(new TextDocument(file.c_str()));
	}

	for (auto entry : index.query("escuela"))
	{
		cout << entry->getFileName() << endl;
	}

<<<<<<< HEAD
=======
=======
		index.add(new TextDocument(file));
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
>>>>>>> Creation of the DBEngine
>>>>>>> Creation of the DBEngine
	cin.get();
	return 0;
}

