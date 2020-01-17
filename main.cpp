#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;
vector<string>combine_cities(vector<string> available_cities);
vector<string> read_available_cities();
int write_to_file(vector<string> cities_list);
vector<string> pre_sort(vector<string> available_cities);
bool comp(string a,  string b) {

	return (a[0] < b[0]);
};
bool comp1(string a,  string b) {

	return (a[a.size() - 1]<b[b.size() - 1]);
};
bool comp2(string a,  string b) {

	return (a.size()>b.size());
};

int main()
{
	//setlocale(LC_ALL, "rus");
	//setlocale(0, "");
	vector<string> available_cities = read_available_cities();
	available_cities = pre_sort(available_cities);

	vector<string>::iterator it;
int n,s(0);


	for (it = available_cities.begin(), n = 1; it != available_cities.end(); ++it, ++n)
	{
		s += it->size();
		cout << "	" << n << "  " << *it << "   "<< s << endl;

	}
	cin.get();

	vector<string> cities_list = combine_cities(available_cities); // TODO implement this function

	write_to_file(cities_list);
	return 0;
}

vector<string> read_available_cities() {
	using namespace std;
	string line;
	ifstream input_file("e:\\input.txt");
	
	vector<string> available_cities;
	while (getline(input_file, line))
	{
		available_cities.push_back(line);
	}
	input_file.close();

	return available_cities;
}

int write_to_file(vector<string> cities_list) {
	ofstream output_file("./output.txt");
	ostream_iterator<string> output_iterator(output_file, "\n");
	copy(cities_list.begin(), cities_list.end(), output_iterator);

	return 0;
}
//////definition pre_sort
vector<string> pre_sort(vector<string> available_cities) {
	vector<string> temp;
	vector<string> smart;

	vector<string>::iterator it;
	vector<string>::iterator pt;

	sort(available_cities.begin(), available_cities.end(), comp);
	//СМАРТ сортировка:)
	char i;
	for (it = available_cities.begin(), i = (*it)[0]; it != available_cities.end(); ++it)
	{
		if (i != (*it)[0])
		{
			i = (*it)[0]; sort(temp.begin(), temp.end(), comp1);
			for (pt = temp.begin(); pt != temp.end(); ++pt)smart.push_back(*pt);
			temp.clear();
			temp.push_back(*it);
		}
		else {
			temp.push_back(*it);
			if ((it + 1) == available_cities.end())
			{
				sort(temp.begin(), temp.end(), comp1);
				for (pt = temp.begin(); pt != temp.end(); ++pt)smart.push_back(*pt);
				temp.clear();
			}
		}

	}
	
	//part twoo (сортировка по длине слова)
	available_cities.clear();
	for (it = smart.begin(), i = (*it)[it->size() - 1]; it != smart.end(); ++it)
	{
		if (i != (*it)[it->size() - 1])
		{
			i = (*it)[it->size() - 1]; sort(temp.begin(), temp.end(), comp2);
			for (pt = temp.begin(); pt != temp.end(); ++pt)available_cities.push_back(*pt);
			temp.clear();
			temp.push_back(*it);
		}
		else {
			temp.push_back(*it);
			if ((it + 1) == smart.end())
			{
				sort(temp.begin(), temp.end(), comp2);
				for (pt = temp.begin(); pt != temp.end(); ++pt)available_cities.push_back(*pt);
				temp.clear();
			}
		}

	}
	return available_cities;
}
