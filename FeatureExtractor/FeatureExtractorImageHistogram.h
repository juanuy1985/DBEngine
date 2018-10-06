#ifndef FEATURE_EXTRACTOR_IMAGE_HISTOGRAM_H
#define FEATURE_EXTRACTOR_IMAGE_HISTOGRAM_H

#include <vector>

#include "FeatureExtractor.h"
#include "../MetricObject/ImageDocument.h"

using namespace std;

namespace jvr
{
	class FeatureExtractorImageHistogram: public FeatureExtractor< vector<double>, ImageDocument >
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

			int cell = 64;
			int div = 256/cell;

			vector<double>* features = new vector<double>(cell * cell * cell, 0.0);

			unsigned int index = 0;

			for(unsigned int y=0; y<image->height() ;y++)
			{
				for(unsigned int x=0; x<image->width() ;x++)
				{
					Pixel* pixel = image->getPixel(x, y);

					// index = (pixel->r/4) + (pixel->g/4) * 64 + (pixel->b/4) * 64 * 64;
	
					index = pixel->r/div + pixel->g/div * cell + pixel->b/div * cell * cell; 

					(*features)[index] += 1;
				}
			}
			normalize(*features);
			return features;
		}
	};
}

#endif
