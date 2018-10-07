#ifndef FEATURE_EXTRACTOR_IMAGE_HISTOGRAM_H
#define FEATURE_EXTRACTOR_IMAGE_HISTOGRAM_H

#include <vector>
#include <cmath>
#include "FeatureExtractor.h"
#include "../MetricObject/ImageDocument.h"

using namespace std;

namespace jvr
{
	class FeatureExtractorHaar: public FeatureExtractor< vector<double>, ImageDocument >
	{
	public:
		void normalize(vector<double>& features)
		{
			double sum = 0.0;
			for(unsigned int index=0; index<features.size() ;index++)
			{
				sum += features[index] * features[index];
			}
			sum = sqrt(sum);

			for(unsigned int index=0; index<features.size();index++)
			{
				features[index] = features[index]/sum;
			}
		}

		vector<double>* getFeatures(ImageDocument* image)
		{
			vector<double>* features = new vector<double>();
			CImg<unsigned char> wavelet = image->haar();

			ImageDocument id(&wavelet);
			double value = 0.0;
			for(unsigned int y=0; y<32;y++){
				for(unsigned int x=0; x<32;x++)
				{
					Pixel* pixel = id.getPixel(x, y);	
					features->push_back(sqrt(pixel->r*pixel->r + pixel->g * pixel->g + pixel->b * pixel->b));	
				}
			}

			normalize(*features);
			return features;
		}
	};
}

#endif
