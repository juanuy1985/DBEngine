#ifndef INDEX_VECTOR_TEXT_DOCUMENT_H
#define INDEX_VECTOR_TEXT_DOCUMENT_H

#include "Index.h"
#include "../MetricObject/TextDocument.h"
#include "../FeatureExtractor/FeatureExtractorTextDocument.h"
#include "../Preprocessor/PreprocessorTextDocument.h"

#include <vector>
#include <map>
#include <iostream>
#include <limits>


using namespace std;

namespace jvr
{
	class IndexVectorTextDocument: public Index<map<string, int>, TextDocument>
	{
		private:
			set<string> dictionary;
			vector<pair<map<string, int>*, TextDocument*>> documents;
			function<double(vector<double>&, vector<double>&)> distanceCalculator;
		public: 
			IndexVectorTextDocument(PreprocessorTextDocument* preprocessor, FeatureExtractorTextDocument* extractor, function<double(vector<double>&, vector<double>&)> distanceCalculator) : Index(preprocessor, extractor)
			{
				this->distanceCalculator = distanceCalculator;
			}

			void indexObject( TextDocument* document, map<string,int>* features )
			{
				documents.push_back(pair<map<string, int>*, TextDocument*>(features, document));

				for(auto word : *features)
				{
					dictionary.insert(word.first);
				}
			}

				
			set<TextDocument*> query( TextDocument* query )
			{				
				set<TextDocument*> result;
				preprocessor->preprocess(query);
				map<string, int>* features = featureExtractor->getFeatures(query);
				TextDocument* tmpDocument = NULL;
				double distance = numeric_limits<double>::max();
				for(auto document : documents)
				{
					double tmpDistance = getDistance(features, document.first);
					if(tmpDistance < distance)
					{
						distance = tmpDistance;
						tmpDocument = document.second;
					}	
				}

				cout<<"Distancia menor: "<<distance<<endl;

				result.insert(tmpDocument);
				return result;	
			}

		private:

			double getDistance(map<string, int>* doc1, map<string, int>* doc2)
			{
				vector<double> featuresAsVector1;
				vector<double> featuresAsVector2;

				for(string word : dictionary)
				{
					auto it1 = doc1->find(word);
					auto it2 = doc2->find(word);

					featuresAsVector1.push_back(it1 == doc1->end() ? 0 : it1->second);
					featuresAsVector2.push_back(it2 == doc2->end() ? 0 : it2->second);
				}

				return distanceCalculator(featuresAsVector1, featuresAsVector2);
			}
	};
}

#endif


