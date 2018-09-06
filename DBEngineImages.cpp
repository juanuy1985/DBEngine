#include "MetricObject/ImageDocument.h"
#include "FeatureExtractor/FeatureExtractorImageDocumentGrid100x100.h"
#include "Preprocessor/PreprocessorImageDefault.h"
#include "Index/IndexVectorImage.h"
#include <iostream>

using namespace std;
using namespace jvr;

int main()
{
	vector<string> images;
	images.push_back("Resources/Files/jpg/desierto01.jpg");
	//images.push_back("Resources/Files/jpg/desierto02.jpg");
	images.push_back("Resources/Files/jpg/desierto03.jpg");
	images.push_back("Resources/Files/jpg/desierto04.jpg");
	images.push_back("Resources/Files/jpg/desierto05.jpg");

	images.push_back("Resources/Files/jpg/playa01.jpg");
	images.push_back("Resources/Files/jpg/playa02.jpg");
	images.push_back("Resources/Files/jpg/playa03.jpg");
	images.push_back("Resources/Files/jpg/playa04.jpg");
	//images.push_back("Resources/Files/jpg/playa05.jpg");


	FeatureExtractorImageDocumentGrid100x100* extractor = new FeatureExtractorImageDocumentGrid100x100();
	PreprocessorImageDefault* preprocessor = new PreprocessorImageDefault();

	IndexVectorImage index(preprocessor, extractor);
	for(string fileName : images)
	{
		ImageDocument* object = new ImageDocument(fileName);
		index.add(object);
	}

	ImageDocument* q = new ImageDocument("Resources/Files/jpg/desierto02.jpg");
	set<ImageDocument*> result = index.query(q);
	
	cout<<"Resultado de la consulta: "<<endl;

	for(ImageDocument* document : result)
	{
		cout<<document->getFilePath()<<endl;
	}

	delete(extractor);
	delete(preprocessor);
	return 0;
}
