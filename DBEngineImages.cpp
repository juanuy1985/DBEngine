#include "MetricObject/ImageDocument.h"
#include "FeatureExtractor/FeatureExtractorImageHistogram.h"
#include "FeatureExtractor/FeatureExtractorImageDocumentGrid100x100.h"
#include "Preprocessor/PreprocessorImageDefault.h"
#include "Index/IndexVectorImage.h"
#include "Index/IndexVPT.h"
#include "Common/Distances.h"
#include <iostream>
#include <functional>

using namespace std;
using namespace jvr;

int main()
{
	string fileName = "Resources/Files/jpg/desierto01.jpg";
	ImageDocument* img = new ImageDocument(fileName);
	img->resize(256, 256);
	CImg<unsigned char> h = img->haar();

	h.save("haar.jpg");

	delete(img);
	return 0;
}

int main1(int arg, char** argv)
{
	if (arg > 1)
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

		images.push_back("Resources/Files/jpg/bosque01.jpg");
		images.push_back("Resources/Files/jpg/bosque02.jpg");
		images.push_back("Resources/Files/jpg/bosque03.jpg");
		images.push_back("Resources/Files/jpg/bosque04.jpg");
		images.push_back("Resources/Files/jpg/bosque05.jpg");
		images.push_back("Resources/Files/jpg/bosque06.jpg");

		images.push_back("Resources/Files/jpg/Lena.jpg");

		auto extractor = new FeatureExtractorImageHistogram();
		//auto extractor = new FeatureExtractorImageDocumentGrid100x100();
	
		auto preprocessor = new PreprocessorImageDefault();

		IndexVectorImage index(preprocessor, extractor, EuclideanDistance);
	
		cout<<"Comenzando la indexación..."<<endl;

		for(string fileName : images)
		{
			ImageDocument* object = new ImageDocument(fileName);
			index.add(object);
		}	

		cout<<"Indexación Finalizada."<<endl;

		ImageDocument* q = new ImageDocument(argv[1]);
	
		index.print(q);
		/*set<ImageDocument*> result = index.query(q);
	
		cout<<"Resultado de la consulta: "<<endl;

		for(ImageDocument* document : result)
		{
			cout<<document->getFilePath()<<endl;
		}*/

		delete(extractor);
		delete(preprocessor);
		return 0;
	}
}
