#include <string>
#include <iostream>
#include <vector>


using namespace std;

void BubbleSort(vector <string> str, bool cmp(string a, string b)){
	int size = str.size();

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size- i - 1; j++)
			if (cmp(str[j], str[j+1]))
				swap(str[j], str[j + 1]);

	for (int i = 0; i < size; i++)
		cout << str[i] << ' ';
	cout << endl;
}


int main() {

	vector <string> b = { "asd","jngej", "uhoerhgfjnvld", "cxv"};


	auto f1 = [](string a, string b) {return a.size() > b.size(); };
	auto f2 = [](string a, string b) {return a.size() < b.size(); };
	auto f3 = [](string a, string b) {return a[0] > b[0]; };
	auto f4 = [](string a, string b) {return a[0] < b[0]; };
	auto f5 = [](string a, string b) {return a[a.size()-1] > b[b.size()-1]; };

	BubbleSort(b,f1);
	BubbleSort(b, f2);
	BubbleSort(b, f3);
	BubbleSort(b, f4);
	BubbleSort(b, f5);

	//cout << f(b[2], b[3]);

	getchar();

	return 1;
}