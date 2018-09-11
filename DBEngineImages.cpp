#include "MetricObject/ImageDocument.h"
#include "FeatureExtractor/FeatureExtractorImageHistogram.h"
#include "Preprocessor/PreprocessorImageDefault.h"
#include "Index/IndexVectorImage.h"
#include "Common/Distances.h"
#include <iostream>

using namespace std;
using namespace jvr;

int main()
{
	vector<string> images;
	images.push_back("Resources/Files/jpg/desierto01.jpg");
	images.push_back("Resources/Files/jpg/desierto02.jpg");
	images.push_back("Resources/Files/jpg/desierto03.jpg");
	images.push_back("Resources/Files/jpg/desierto04.jpg");
	images.push_back("Resources/Files/jpg/desierto05.jpg");

	images.push_back("Resources/Files/jpg/playa01.jpg");
	images.push_back("Resources/Files/jpg/playa02.jpg");
	images.push_back("Resources/Files/jpg/playa03.jpg");
	images.push_back("Resources/Files/jpg/playa04.jpg");
	images.push_back("Resources/Files/jpg/playa05.jpg");

	images.push_back("Resources/Files/jpg/Lena.jpg");

	auto extractor = new FeatureExtractorImageHistogram();
	
	auto preprocessor = new PreprocessorImageDefault();

	IndexVectorImage* index = new IndexVectorImage(preprocessor, extractor, EuclideanDistance);
	
	cout<<"Comenzando la indexación..."<<endl;

	for(string fileName : images)
	{
		ImageDocument* object = new ImageDocument(fileName);
		index->add(object);
	}

	cout<<"Indexación Finalizada."<<endl;

	ImageDocument* q = new ImageDocument("Resources/Files/jpg/playa03.jpg");
	set<ImageDocument*> result = index->query(q);
	
	cout<<"Resultado de la consulta: "<<endl;

	for(ImageDocument* document : result)
	{
		cout<<document->getFilePath()<<endl;
	}

	delete(extractor);
	delete(preprocessor);
	return 0;
}
