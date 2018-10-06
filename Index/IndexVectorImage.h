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
#include "../FeatureExtractor/FeatureExtractor.h"

using namespace std;

namespace jvr
{
	class IndexVectorImage : public Index< vector<double>, ImageDocument>
	{
	private:
		vector<pair<vector<double>*, ImageDocument*>> structure;
		function<double(vector<double>&, vector<double>&)> distanceCalculator;
	public:
		IndexVectorImage(PreprocessorImageDefault* preprocessor, FeatureExtractor<vector<double>, ImageDocument>* featureExtractor, function<double(vector<double>&, vector<double>&)> distanceCalculator) : Index(preprocessor, featureExtractor)
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
				
				cout<<tuple.second->getFilePath()<<": "<<distance<<endl;

				if(lessDistance > distance)
				{
					similar = tuple.second;
					lessDistance = distance;
				}
			}
			result.insert(similar);
			return result;
		}

		void print(ImageDocument* query) {
			double distance = 0.0;
			vector<pair<double, ImageDocument*>> order;
			auto features = this->featureExtractor->getFeatures(query);
                        for(auto tuple : structure)
                        {
                                distance = distanceCalculator( *features, *(tuple.first) );
				order.push_back(pair<double,ImageDocument*>(distance, tuple.second));
                        }
			sort(order.begin(), order.end());
			for(auto tuple : order)
			{
				cout<<tuple.second->getFilePath()<<": "<<tuple.first<<endl;
			}
		}
	};
}

#endif
