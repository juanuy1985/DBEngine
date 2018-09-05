#include "Preprocessor/PreprocessorTextDocument.h"
#include "FeatureExtractor/FeatureExtractorTextDocument.h"
#include "Index/InvertedIndex.h"
#include "Common/util.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace jvr;

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
	
	PreprocessorTextDocument preprocessor;
	FeatureExtractorTextDocument extractor;
	InvertedIndex index(&preprocessor, &extractor);

	for (string file : files)
	{
		index.add(new TextDocument(file.c_str()));
	}

	for (auto entry : index.query("escuela"))
	{
		cout << entry->getFileName() << endl;
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

