#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

void Buble(vector<string> &vector, function<bool(string, string)> function)
{
	int SizeVector = vector.size();
	string tmp;
	bool swapped = false;
	for (int i = 0; i < SizeVector; i++)
	{
		for (int j = 0; j < (SizeVector - i - 1); j++)
		{
			if (function(vector[j], vector[j + 1]))
			{
				tmp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = tmp;
				swapped = true;
			}
		}
		if (!swapped)
		{
			break;
		}
	}
}
int main()
{
	vector<string> VectorString = { "Red","Orange","Yellow", "Green", "Aqua", "Blue", "Purple" };
	vector <int> VectorInteger = { 3,5,1,45,32,7,12,90 };
	for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << endl; });
	cout << endl;


	Buble(VectorString,
		[](string First, string Second) {return (First.size()<Second.size()); });
	for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << endl; });
	cout << endl;


	Buble(VectorString,
		[](string First, string Second) {return First < Second; });
	for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << endl; });
	cout << endl;


	Buble(VectorString,
		[](string First, string Second) {return ((int)First[0]>(int)Second[0]); });
	for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << endl; });
	cout << endl;


	Buble(VectorString,
		[](string First, string Second) {return (Second.size() % 2 == 0 &&
			First.size() % 2 != 0); });
	for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << endl; });
	cout << endl;

	Buble(VectorInteger, 
		[](int First, int Second) {return First < Second; });
	for_each(VectorInteger.begin(), VectorInteger.end(), [](int i) {cout << i << endl; });
	cout << endl;

	system("pause");
}