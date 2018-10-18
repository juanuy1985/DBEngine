#define cimg_use_jpeg
#include "Common/ImageProcessing/CImg.h"
#include <iostream>

using namespace std;
using namespace cimg_library;
int main()
{
        string fileName = "/home/ubuntu/Proyectos/DBEngine/Resources/faces/adhast/adhast.1.jpg";
        CImg<unsigned char>* image = new CImg<unsigned char>(fileName.c_str());
        image->resize(256, 256);
        // convert from unsigned char to float to support larger range of values

	CImg<unsigned char> wavelet = image->haar();

        wavelet.normalize(0,255).save("Resources/Files/FaceHaar.jpg");


	delete(image);

        return 0;
}
