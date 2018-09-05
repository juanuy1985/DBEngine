#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

namespace jvr
{
	template <class F, class T>
	class FeatureExtractor
	{
	public:
		virtual F* getFeatures(T* object) = 0;
	};
}

#endif