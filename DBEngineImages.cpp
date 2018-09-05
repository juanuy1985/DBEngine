#define cimg_use_jpeg
#include "Common/ImageProcessing/CImg.h"
#include <iostream>

using namespace std;
using namespace cimg_library;

struct Pixel
{
	char r,g,b;
};

int main()
{
	CImg<unsigned char> img("Resources/Files/jpg/Lena.jpg");
	
	cout<<img.data();
	return 0;
}
