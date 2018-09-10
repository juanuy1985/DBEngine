#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath>
#include <functional>
#include <vector>

using namespace std;

namespace jvr
{
	auto EuclideanDistance = [](vector<double>& v1, vector<double>&v2) -> double
	{
		double distance = 0;

		for(unsigned int index=0; index<v1.size()  ;index++)
		{
			distance += (v1[index]-v2[index])*(v1[index]-v2[index]);
	
		}
		return sqrt(distance);
	};
}

#endif
