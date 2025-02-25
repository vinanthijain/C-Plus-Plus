#include<iostream>
#include<stdio.h>
#include <sstream>
#include <iomanip>
using namespace std;
int main()
{
	double Latitude=535466458;
	std::stringstream ss;
	double lat = std::abs(Latitude) / 10000000.0;
        int iLat = lat;
        ss << std::setw(2) << std::setfill('0') << iLat << std::setw(9) << std::setfill('0')
           << std::fixed << std::setprecision(6) << (lat - iLat) * 60.0 << ",";
	cout<<ss.str()<<endl;
}
