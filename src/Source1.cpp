#pragma once

#include<iostream>
#include<vector>
#include<string>

using namespace std;

template <class T>
void BubbleSort(vector<T>& v, int(*cmp)(const T& a, const T& b))
{	
	for (int i = 0; i < v.size() - 1; ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (cmp(v[i], v[j]) == 1) {
				T tmp = v[i];
				v[i] = v[j];
				v[j] = tmp;
			}
		}
	}
}

int main()
{
	vector<string> str;
	str.push_back("2");
	str.push_back("1");
	str.push_back("22");
	str.push_back("11");
	str.push_back("5");
	str.push_back("Na");
	str.push_back("an");
	str.push_back("nan5");
	str.push_back("Anna");
	str.push_back("1");
	str.push_back("*50");
	str.push_back("/19");
	str.push_back("hahr");

	BubbleSort<string>(str, 
		[](const string& a, const string& b) -> int {
			if (a < b)
				return -1;
			else if (a == b)
				return 0;
			else if (a > b)
				return 1;
		}
	);
	cout << "first comparation" << endl;
	for (int i = 0; i < str.size(); ++i)
		cout << str[i] << endl;
	cout << endl;

	BubbleSort<string>(str,
		[](const string& a, const string& b) -> int {
			if (a.size() < b.size())
				return -1;
			if (a.size() > b.size())
				return 1;
			return strcmp(a.c_str(), b.c_str());
		}
	);
	cout << "second comparation" << endl;
	for (int i = 0; i < str.size(); ++i)
		cout << str[i] << endl;
	cout << endl;
	
	BubbleSort<string>(str,
		[](const string& a, const string& b) -> int {
			return strcmp(a.c_str(), b.c_str());
		}
	);
	cout << "third comparation" << endl;
	for (int i = 0; i < str.size(); ++i)
		cout << str[i] << endl;
	cout << endl;

	BubbleSort<string>(str,
		[](const string & a, const string & b) -> int {
			if (a[a.length()-1] < b[b.length()-1])
				return -1;
			else if (a[a.length()-1] > b[b.length()-1])
				return 1;
			return 0;
		}
	);
	cout << "fourth comparation" << endl;
	for (int i = 0; i < str.size(); ++i)
		cout << str[i] << endl;
	cout << endl;

	BubbleSort<string>(str,
		[](const string & a, const string & b) -> int {
			return a > b ? -1 : a < b ? 1 : 0;
		}
	);
	cout << "fifth comparation" << endl;
	for (int i = 0; i < str.size(); ++i)
		cout << str[i] << endl;
	cout << endl;
	
	::system("pause");
	return 0;
}
