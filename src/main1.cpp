#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;



void sortBub(vector<string>& vec, const function<bool(string, string)>& fun) {
	int n = vec.size();
	if (n == 0) return;
	int i = 0;
	char swap_cnt = 0;

	while (i < n)
	{
		if (i + 1 != n && fun(vec[i], vec[i + 1]) == 0)
		{
			swap(vec[i], vec[i + 1]);
			swap_cnt = 1;
		}
		i++;
		if (i == n && swap_cnt == 1)
		{
			swap_cnt = 0;
			i = 0;
		}
	}

}


int main() {
	vector<string> v = {"fffff", "bf", "ba", "a", "vvv", "zlkasl", "kkk"};

	sortBub(v, [](string a, string b) {return a <= b;});
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	sortBub(v, [](string a, string b) {return a >= b; });
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	sortBub(v, [](string a, string b) {return a.size() <= b.size(); });
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	sortBub(v, [](string a, string b) {return a[a.size()-1] <= b[b.size()-1];});
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	sortBub(v, [](string a, string b) {
		int maxA = 0;
		int maxB = 0;
		int k = 1;
		for (int i = 0; i < a.size() - 1; i++) {
			for (int j = i + 1; j < a.size(); j++) {
				if (a[i] == a[j]) k++;
			}
			if (k > maxA) maxA = k;
			k = 1;
		}
		for (int i = 0; i < b.size() - 1; i++) {
			for (int j = i + 1; j < b.size(); j++) {
				if (b[i] == b[j]) k++;
			}
			if (k > maxB) maxB = k;
			k = 1;
		}
		return maxA >= maxB; });
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
}