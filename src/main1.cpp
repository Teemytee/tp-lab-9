#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
/*
void BSort(vector<string> vec, bool cmp(string a, string b)) {
	int len = vec.size();
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len-1; j++)
			if (cmp(vec[j], vec[j + 1])) {
				swap(vec[j], vec[j + 1]);
			}
	} 

	for_each(vec.begin(), vec.end(), [](string x) { cout << x << " "; });
	cout << endl;
}

int main() {
	vector<string> a = { "abc", "dsavcxd", "dsad", "ad", "cxv", "fdsf" };

	auto p = [](string a, string b) {return a.size() < b.size(); };

	cout << p("asd", "vcbgf");

	BSort(a, [](string a, string b) {return a.size() < b.size(); });
	BSort(a, [](string a, string b) {return a.size() > b.size(); });
	BSort(a, [](string a, string b) {return a[0] > b[0]; });
	BSort(a, [](string a, string b) {return a[a.size()-1] > b[b.size()-1]; });
	getchar();
	return 1;
}
*/
