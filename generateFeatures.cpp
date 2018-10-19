#define cimg_use_jpeg
#include "Common/ImageProcessing/CImg.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
using namespace cimg_library;

struct Feature
{
	float sum = 0;
	float mean = 0;
	float median = 0;
	float max = 0;
	float min = numeric_limits<float>::infinity();
};

Feature getStatistics(CImg<float>& wavelet){
	vector<float> features;
	Feature result;

	float value = 0;
	for(int y=0; y<32 ;y++)
        {
        	for(int x=0; x<32  ;x++)
                {
			value = wavelet(x,y);
                	features.push_back(value);
			result.sum += value;
			result.min = result.min > value ? value : result.min;
			result.max = result.max < value ? value : result.max;
                }
        }
	result.mean = result.sum / 1024;

	sort(features.begin(), features.end());
	result.median = features[512];
	
	return result;
}

void process(vector<string>& id, vector<string>& pictures)
{
	for(int index=0;index<pictures.size(); index++)
	{
		CImg<float> image(pictures[index].c_str());
		image.resize(256,256);
		CImg<float> wavelet = image.haar(false, 16);
		Feature result = getStatistics(wavelet);
		cout<<id[index]<<", "<<result.sum<<", "<<result.mean<<", "<<result.median<<", "<<result.max<<", "<<result.min<<endl;
	}
}


int main(int argc, char** argv)
{
	if(argc > 1)
	{
		vector<string> ids;
		vector<string> paths;
		string id, path;
		while(getline(cin, id, '@'))
		{
			getline(cin, path);
			ids.push_back(id);
			paths.push_back(path);			
		}

		process(ids, paths);
	}
	return 0;
}


int main1()
{
        string fileName = "/home/ubuntu/Proyectos/DBEngine/Resources/faces/adhast/adhast.1.jpg";
        CImg<float>* image = new CImg<float>(fileName.c_str());
        image->resize(256, 256);
        // convert from unsigned char to float to support larger range of values

	CImg<float> wavelet = image->haar(false, 16);

        wavelet.save("Resources/Files/FaceProcess.jpg");

	delete(image);

        return 0;
}
