#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;

template <class T, class lambda>
void sort(T mas,lambda f) {
	for (int i = mas.size() - 1; i >= 1; i--) {
		for (int i = 0; i < mas.size(); i++) {
			if ((i + 1 != mas.size()) && (f(mas[i], mas[i + 1]))) {
				swap(mas[i], mas[i + 1]);
			}
		}
	}
	for (int i = 0; i < mas.size(); i++) {
		cout << mas[i] << " ";
	}cout << endl<<endl;
}

int main()
{
	vector <string> mas = { "Vincent","Sabrina","Donna","Ethan","Christopher","John","Joleen","Hillary","James" };
	vector <int> array = { 3,5,1,45,32,7,12,90 };

	cout << "Sorting array by word length (ascending)" << endl;
	sort(mas, [](string a, string b) {return a.length() < b.length(); });
	

	cout << "Sorting array by word length (descending)" << endl;
	sort(mas, [](string a, string b) {return a.length() > b.length(); });
	

	cout << "Alphabetical sorting" << endl;
	sort(mas, [](string a, string b) {return a < b; });
	sort(mas, [](string a, string b) {return a > b; });


	cout << "Sort by first letter " << endl;
	sort(mas, [](string a, string b) {return a[0] < b[0]; });


	cout << "Sort int array " << endl;
	sort(array, [](int a, int b) {return a < b; });
	sort(array, [](int a, int b) {return a > b; });
}