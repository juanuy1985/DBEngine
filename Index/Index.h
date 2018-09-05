#ifndef INDEX_H
#define INDEX_H

#include <set>

#include "Preprocessor.h"
#include "FeatureExtractor.h"

using namespace std;

namespace jvr
{
	/*
		F: tipo de objeto que contiene las caracteristicas a extraer
		T: tipo de objeto principal: Imagen, Documento de texto, Video, musica, etc. 
	*/
	template <class F, class T>
	class Index
	{
	private:
		Preprocessor<T>* preprocessor;
		FeatureExtractor<F, T>* featureExtractor;
	public:
		Index(Preprocessor<T>* preprocessor, FeatureExtractor<F, T>* featureExtractor)
		{
			this->preprocessor = preprocessor;
			this->featureExtractor = featureExtractor;
		}

		void add(T* object)
		{
			preprocessor->preprocess(object);
			F* features = featureExtractor->getFeatures(object);
			indexObject(object, features);
		}

		virtual void indexObject(T* object, F* features) = 0;

		/*
			Q: objeto que representa una consulta al indice, este varia por eso se pasa como parámetro
		*/
		template <class Q>
		set<T*> query( Q query );
	};
}

#endif