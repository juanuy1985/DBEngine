#ifndef PREPROCESSOR_IMAGE_DEFAULT_H
#define PREPROCESSOR_IMAGE_DEFAULT_H

#include <algorithm>
#include <fstream>
#include <vector>

#include "Preprocessor.h"
#include "../MetricObject/ImageDocument.h"

using namespace std;

namespace jvr
{
    class PreprocessorImageDefault: public Preprocessor<ImageDocument>
    {
    private:
		
    public:

        PreprocessorImageDefault()
        {
        }

        void preprocess(ImageDocument* image)
        {
		//Este Preprocesador no hace nada 
        }
    };
}

#endif // PREPROCESSOR_IMAGE_DEFAULT_H
