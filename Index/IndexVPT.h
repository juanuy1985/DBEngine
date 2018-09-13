#ifndef INDEX_VPT_H
#define INDEX_VPT_H

#include "Index.h"
#include "../FeatureExtractor/FeatureExtractor.h"
#include "../Preprocessor/Preprocessor.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

namespace jvr
{
	template <class F, class T, class D>
	struct VPTNode
	{
	private:
		pair<F*, T*> middleObject;
		VPTNode<F, T, D>* left;
		VPTNode<F, T, D>* right;
		int leftChildrenSize;
		int rightChildrenSize;
		double middleDistance;
	public:
		
		VPTNode(vector<pair<F*, T*>>& objects, D distanceCalculator)
		{
			srand(time(0));						// Inicializa la generacion de randoms
			int indexMiddlePoint = rand() % objects.size(); 	// elegimos el punto medio al azar
			middleObject = objects[indexMiddlePoint];


			// Genero las distancias al objeto medio y luego de eso las ordeno
			vector<pair<double, int>> distances;
			for(int index=0; index<objects.size() ;index++)
			{
				auto object = objects[index];
				distances.push_back(pair<double, int>(distanceCalculator(*middleObject.first, *object.first), index));
			}
			sort(distances.begin(), distances.end());
			this->middleDistance = distances[distances.size()/2].first;
		
			int middle = distances.size()/2;
			vector<pair<F*, T*>> leftChildren;
			vector<pair<F*, T*>> rightChildren;
			for(int index=0; index<middle ;index++)
				if(indexMiddlePoint != distances[index].second) //No insertar el objeto middleObject
					leftChildren.push_back(objects[distances[index].second]);
				
			for(int index=middle; index<distances.size() ;index++)
				if(indexMiddlePoint != distances[index].second) //No insertar el objeto middleObject
					rightChildren.push_back(objects[distances[index].second]);

			leftChildrenSize = leftChildren.size();
			rightChildrenSize = rightChildren.size();

			left = leftChildren.size() == 0 ? NULL : new VPTNode<F, T, D>(leftChildren, distanceCalculator);
			right = rightChildren.size() == 0 ? NULL : new VPTNode<F, T, D>(rightChildren, distanceCalculator);
		}


		~VPTNode()
		{
			if (left != NULL)
				delete(left);
	
			if (right != NULL)
				delete(right);
		}

		
		set<T*> query(F* queryObject, D distanceCalculator, int numberObjects)
		{
			double distance = distanceCalculator(*queryObject, *middleObject.first);
		
			if (distance < middleDistance)
			{
				if (leftChildrenSize <= numberObjects )
					return subTreeAsSet(left);
				return left->query(queryObject, distanceCalculator, numberObjects);
			}
			else
			{
				if (rightChildrenSize <= numberObjects )
					return subTreeAsSet(right);
				return right->query(queryObject, distanceCalculator, numberObjects);
			}
		}

		set<T*> subTreeAsSet(VPTNode<F, T, D>* node)
		{
			set<T*> result;
			fillSet(result, node);
			return result;
		}

		void fillSet(set<T*>& result, VPTNode<F, T, D>* node)
		{
			result.insert(node->middleObject.second);
			
			if (node->left != NULL)
				fillSet(result, node->left);

			if (node->right != NULL)
				fillSet(result, node->right);
		}
	};


	template <class F, class T, class D>
	class IndexVPT : public Index<F, T>
	{
	private:
		vector<pair<F*, T*>> objects;
		D distanceCalculator;
		VPTNode<F, T, D>* root;
	public:
		IndexVPT(Preprocessor<T>* preprocessor, FeatureExtractor<F, T>* extractor, D distanceCalculator) : Index<F, T>(preprocessor, extractor)
		{
			this->distanceCalculator = distanceCalculator;
			root = NULL;
		}

		~IndexVPT()
		{
			if (root != NULL)
				delete(root);
		}
		
		void indexObject(T* object, F* features)
		{
			objects.push_back(pair<F*, T*>(features, object));

			if (root != NULL)
				delete(root);

			root = NULL;			
		}


		void buildVPT()
		{
			if (root != NULL)
				delete(root);	// Si existia un arbol anterior lo eliminamos 
			
			if (objects.size() > 0)
				root = new VPTNode<F, T, D>(objects, distanceCalculator); 
		}
                
		set<T*> query( T* queryObject )
		{
			return query(queryObject, 1);
		}

		set<T*> query( T* queryObject, int numberObjects )
		{
			if (root == NULL)
				buildVPT();

			if (objects.size() <= numberObjects )
				return root->subTreeAsSet(root);
			
			this->preprocessor->preprocess(queryObject);
			F* features = this->featureExtractor->getFeatures(queryObject);
	
			return root->query(features, distanceCalculator, numberObjects);
		}
	};
}

#endif
