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
		vector<double>* getFeatures(ImageDocument* image)
		{

			vector<double>* features = new vector<double>(64 * 64 * 64, 0.0);

			unsigned int index = 0;

			for(unsigned int y=0; y<image->height() ;y++)
			{
				for(unsigned int x=0; x<image->width() ;x++)
				{
					Pixel* pixel = image->getPixel(x, y);

					index = (pixel->r/4) + (pixel->g/4) * 64 + (pixel->b/4) * 64 * 64;
	
					(*features)[index] += 1;
				}
			}
			
			return features;
		}
	};
}

#endif
