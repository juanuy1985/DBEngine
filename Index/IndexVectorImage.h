#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <set>
#include <cmath>

#include "Index.h"
#include "../MetricObject/ImageDocument.h"
#include "../Preprocessor/PreprocessorImageDefault.h"
#include "../FeatureExtractor/FeatureExtractorImageDocumentGrid100x100.h"

using namespace std;

namespace jvr
{
	class IndexVectorImage : public Index< vector<float>, ImageDocument>
	{
	private:
		vector<pair<vector<float>*, ImageDocument*>> structure;

		float getDistance( vector<float>& v1, vector<float>& v2 )
		{
			float result = 0;

			for(int index=0; index<v1.size() ;index++ )
			{
				result += (v1[index]-v2[index]) * (v1[index]-v2[index]);
			}

			return sqrt(result);
		}


	public:
		IndexVectorImage(PreprocessorImageDefault* preprocessor, FeatureExtractorImageDocumentGrid100x100* featureExtractor) :Index(preprocessor, featureExtractor)
		{

		}

		void indexObject( ImageDocument* image, vector<float>* features )
		{
			structure.push_back( pair<vector<float>*, ImageDocument*>(features, image) );
		}

		set<ImageDocument*> query(ImageDocument* query)
		{
			set<ImageDocument*> result;
			auto features = this->featureExtractor->getFeatures(query);
			ImageDocument* similar = NULL;
			float lessDistance = 1000000000, distance = 0;
			for(auto tuple : structure)
			{
				distance = getDistance( *features, *(tuple.first) );
				if(lessDistance > distance)
				{
					similar = tuple.second;
					lessDistance = distance;
				}
			}
			result.insert(similar);
			return result;
		}
	};
}

#endif
