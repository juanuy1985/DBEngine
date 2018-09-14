#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath>
#include <functional>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace jvr
{
	auto EuclideanDistance = [](vector<double>& v1, vector<double>&v2) -> double
	{
		double distance = 0;

		for (unsigned int index=0; index<v1.size()  ;index++)
		{
			distance += (v1[index]-v2[index])*(v1[index]-v2[index]);
	
		}

		return sqrt(distance);
	};

	auto EuclideanDistanceBasedMaps = [](map<string,int>& m1, map<string,int>& m2) -> double
	{
		double distance = 0;
		set<string> intersection;

		for (auto pairM1 : m1)
		{
			auto pairM2 = m2.find(pairM1.first);
			if (pairM2 != m2.end()) // Tambien se encontro el elemento en el segundo mapa
			{
				intersection.insert(pairM1.first);
				distance += (pairM1.second - pairM2->second) * (pairM1.second - pairM2->second);
			}
			else
			{
				distance += pairM1.second * pairM1.second;
			}
		}

		
		for (auto pairM2 : m2)
		{
			if (intersection.find(pairM2.first) == intersection.end())
			{
				distance += pairM2.second * pairM2.second;
			}
		}

		return sqrt(distance);
	};
}

#endif
