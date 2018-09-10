#ifndef FEATURE_EXTRACTOR_IMAGE_DOCUMENT_GRID_100_X_100_H
#define FEATURE_EXTRACTOR_IMAGE_DOCUMENT_GRID_100_X_100_H

#include <vector>

#include "FeatureExtractor.h"
#include "../MetricObject/ImageDocument.h"

using namespace std;

namespace jvr
{
	class FeatureExtractorImageDocumentGrid100x100: public FeatureExtractor< vector<double>, ImageDocument >
	{
	public:
		vector<double>* getFeatures(ImageDocument* image)
		{

			int blockDimensionX = image->width() / 100;
			int blockDimensionY = image->height() / 100;

			int currentX = 0, currentY = 0;
			vector<double>* features = new vector<double>(10000,0);
			for(int y=0; y<100 ;y++)
			{
				for(int x=0; x<100 ;x++)
				{
					currentX = x*blockDimensionX;
					currentY = y*blockDimensionY;

					for(int j=0;j<blockDimensionY;j++)
						for(int i=0; i<blockDimensionX ;i++)
						{
							Pixel* pixel = image->getPixel(currentX+i, currentY+j);
							(*features)[y*100+x] += (pixel->r + pixel->g + pixel->b) / 3.0;
						} 
					(*features)[y*100+x] /= blockDimensionX * blockDimensionY;
				}
			}

			return features;
		}
	};
}

#endif
