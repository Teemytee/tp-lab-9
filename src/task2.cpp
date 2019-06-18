#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
bool printFlag = true;
mutex Mu;
bool EF = false;
template <class T>
void BubbleSort(vector<T>& v, int(*cmp)(const T& a, const T& b))
{	
	for (int i = 0; i < v.size() - 1; ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (cmp(v[i], v[j]) == 1) {
				Mu.lock();
				if (printFlag == false) {
					T tmp = v[i];
					v[i] = v[j];
					v[j] = tmp;
					printFlag = true;
				}
				Mu.unlock();
				this_thread::yield();
			}
		}
	}
	EF = true;
}

int main()
{
	vector<string> str;
	str.push_back("2");
	str.push_back("1");
	str.push_back("22");
	str.push_back("11");

	thread Sorter(
		[&]() -> void {
			BubbleSort<string>(str,
				[](const string& a, const string& b) -> int {
					return strcmp(a.c_str(), b.c_str());
				}
			);
		}
	);

	while (true) {
		Mu.lock();
		if (printFlag == true) {
			for (int i = 0; i < str.size(); ++i) {
				cout << str[i] << " ";
			}
			cout << endl;
			printFlag = false;
		}
		Mu.unlock();
		if (EF == true)
			break;
	}

	for (int i = 0; i < str.size(); ++i) {
		cout << str[i] << endl;
	}

	Sorter.detach();
	
	::system("pause");
	return 0;
}
