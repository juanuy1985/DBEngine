#include "Common/ImageProcessing/CImg.h"
#include <iostream>

using namespace cimg_library;
using namespace std;

int main()
{
	const char* fileName = "Resources/Files/jpg/Face01.jpg";
	CImg<unsigned char> img(fileName);
	CImg<float> fft_in = img;
	fft_in.resize(256, 256);
	// convert from unsigned char to float to support larger range of values

	// Forward transform
	CImgList<float> fft = fft_in .get_FFT();

	// Inverse transform
	CImg<float>::FFT(fft[0], fft[1], true);

	// Normalize back to unsigned char range (0,255) and save
	fft[0].normalize(0,255).save("img/fft.png");
	return 0;
}

