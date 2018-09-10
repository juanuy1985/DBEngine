#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <set>
#include <cmath>
#include <functional>
#include <limits>

#include "Index.h"
#include "../MetricObject/ImageDocument.h"
#include "../Preprocessor/PreprocessorImageDefault.h"
#include "../FeatureExtractor/FeatureExtractorImageDocumentGrid100x100.h"

using namespace std;

namespace jvr
{
	class IndexVectorImage : public Index< vector<double>, ImageDocument>
	{
	private:
		vector<pair<vector<double>*, ImageDocument*>> structure;
		function<double(vector<double>&, vector<double>&)> distanceCalculator;
	public:
		IndexVectorImage(PreprocessorImageDefault* preprocessor, FeatureExtractorImageDocumentGrid100x100* featureExtractor, function<double(vector<double>&, vector<double>&)> distanceCalculator) : Index(preprocessor, featureExtractor)
		{
			this->distanceCalculator = distanceCalculator;
		}

		void indexObject( ImageDocument* image, vector<double>* features )
		{
			structure.push_back( pair<vector<double>*, ImageDocument*>(features, image) );
		}

		set<ImageDocument*> query(ImageDocument* query)
		{
			set<ImageDocument*> result;
			auto features = this->featureExtractor->getFeatures(query);
			ImageDocument* similar = NULL;
			double lessDistance = numeric_limits<double>::max(), distance = 0;
			for(auto tuple : structure)
			{
				distance = distanceCalculator( *features, *(tuple.first) );
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
