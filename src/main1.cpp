#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <thread>
using namespace std;
#define N 5

void bubbleSort(string** str, bool Comparator(string, string)) {
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (Comparator((*str)[j], (*str)[j + 1])) {
				swap((*str)[j], (*str)[j + 1]);
			}
		}
	}
}

int main()
{
	string str[N] = { "Lupa Lupova-Lupeeva", "Pupa Pa", "Kepa Kepovna", "Mepa Mepeeva", "Feta Fetovna"};
	string** ptr = new string*[N];
	for (int i = 0; i < N; i++) {
		ptr[i] = str + i;
	}
	//int n = sizeof(str)/sizeof(str[0]);
	auto Comparator1 = [](string str1, string str2) {return str1 > str2 ? true : false;};
	auto Comparator2 = [](string str1, string str2) {return str1 < str2 ? true : false; };
	auto Comparator3 = [](string str1, string str2) {return (&str1)->length() > (&str2)->length() ? true : false; };
	auto Comparator4 = [](string str1, string str2) {return (&str1)->length() < (&str2)->length() ? true : false; };
	auto Comparator5 = [](string str1, string str2) {return (((&str1)->length() % 12 == 0)&&((&str2)->length() % 12 == 0)) ? true : false; };
	
	bubbleSort(ptr, Comparator1);
	for (auto s:str)cout << s << endl;
	cout << endl;
	bubbleSort(ptr, Comparator2);
	for (auto s : str)cout << s << endl;
	cout << endl;
	bubbleSort(ptr, Comparator3);
	for (auto s : str)cout << s << endl;
	cout << endl;
	bubbleSort(ptr, Comparator4);
	for (auto s : str)cout << s << endl;
	cout << endl;
	bubbleSort(ptr, Comparator5);
	for (auto s : str)cout << s << ' ' << (&s)->length() << endl;
	cout << endl;
	//system("pause");
	return 0;
}