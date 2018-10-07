#ifndef IMAGE_DOCUMENT_H
#define IMAGE_DOCUMENT_H

#define cimg_use_jpeg
#include "../Common/ImageProcessing/CImg.h"

#include <iostream>

using namespace cimg_library;
using namespace std;

namespace jvr
{
	struct Pixel
	{
		unsigned char r,g,b;
	};

	class ImageDocument
	{
	private:
		CImg<unsigned char>* image;
		string filePath;
	public:
		ImageDocument(CImg<unsigned char>* image)
		{
			this->image = image;
			this->filePath = "";
		}	

		ImageDocument(string filePath)
		{
			this->filePath = filePath;
			image = new CImg<unsigned char>(filePath.c_str());
		}

		~ImageDocument()
		{
			if(filePath != "")
				delete(image);
		}

		int width()
		{
			return image->width();
		}

		int height()
		{
			return image->height();
		}

		Pixel* getAllPixels()
		{
			return (Pixel*)image->data();
		}

		inline Pixel* getPixel(int x, int y)
		{
			return (Pixel*)&(image->data()[y*image->width()*3+x*3]);
		}

		string getFilePath()
		{
			return filePath;
		}

		CImg<unsigned char> haar()
		{
			return image->haar(false, 2);	
		}

		void resize(int width, int height)
		{
			image->resize(width, height);
		}
	};
}

#endif
