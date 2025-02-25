#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
	vector<string> lines;
	string line;
	ifstream input_file("/home/vinanthi/Downloads/analytics_test.xlsx");
	if(!input_file.is_open())
	{
		cout<<"File not open"<<endl;
		return 0;
	}
	while (getline(input_file, line)){
        lines.push_back(line);
    }

    for (const auto &i : lines)
        cout << i << endl;

    input_file.close();
    return 1;
}
