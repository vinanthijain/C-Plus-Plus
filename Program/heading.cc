#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
	bool isInReverse = false;
	float angle = 3420.0;
        if (isInReverse) {
            angle += 180.0;
        }

        while (angle >= 360.0) {
            angle -= 360.0;
        }
	cout<<"angle="<<angle;
}
