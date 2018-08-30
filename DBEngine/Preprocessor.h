#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

namespace jvr
{
    template <class T>
    class Preprocessor
    {
    public:
        virtual void preprocess(T* object) = 0;
    };
}

#endif // PREPROCESSOR_H
