#include "MetricObject/ImageDocument.h"
// #include "FeatureExtractor/FeatureExtractorImageHistogram.h"
// #include "FeatureExtractor/FeatureExtractorImageDocumentGrid100x100.h"
#include "FeatureExtractor/FeatureExtractorHaar.h"
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
	string fileName = "Resources/Files/jpg/Face.jpg";
	CImg<float> fft_in(fileName);
	fft_in.resize(256, 256);
	// convert from unsigned char to float to support larger range of values

	// Forward transform
	CImgList<float> fft = fft_in .get_FFT();

	// Inverse transform
	CImg<float>::FFT(fft[0], fft[1], true);

	// Normalize back to unsigned char range (0,255) and save
	fft[0].normalize(0,255).save("img/fft.png");
	return 0;
}

int main2(int arg, char** argv)
{
	if (arg > -1)
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

		images.push_back("Resources/Files/jpg/Face01.jpg");

		auto extractor = new FeatureExtractorHaar();
		//auto extractor = new FeatureExtractorImageDocumentGrid100x100();
	
		auto preprocessor = new PreprocessorImageDefault();

		IndexVectorImage index(preprocessor, extractor, EuclideanDistance);
	
		cout<<"Comenzando la indexación..."<<endl;

		for(string fileName : images)
		{
			ImageDocument* object = new ImageDocument(fileName);
			object->resize(256, 256);
			index.add(object);
		}	

		cout<<"Indexación Finalizada."<<endl;

		ImageDocument* q = new ImageDocument("Resources/Files/jpg/Face.jpg");
		q->resize(256, 256);	
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
