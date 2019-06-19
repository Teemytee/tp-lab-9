#include <iostream>
#include <vector>
#include<string>
#include <functional>
#include <algorithm>
using namespace std;

void BubbleSort(vector<string>myVec, bool cmp(string a, string b))
{	
	cout << "Before BubbleSort:\n";
	for (auto i : myVec)
		cout << i << " ";
	cout << endl;
	for(int i=0;i<myVec.size();i++)
		for (int j = 0; j < myVec.size()-1; j++)
		{
			if (cmp(myVec[j], myVec[j+1]))
				swap(myVec[j], myVec[j+1]);
		}
	cout << "After BubbleSort:\n";
	for (auto i : myVec)
		cout << i << " ";
	cout << endl;
}

int main()
{
	vector<string>forSort = { "Zyxwp","Abc","LMNBHJ","18uhgsp","0008","qwertyyy" };

	cout << "Sort by first element (greater)\n";
	BubbleSort(forSort, [](string a, string b) {	return a[0] > b[0]; });
	cout << endl;

	cout << "Sort by last element (greater)\n";
	BubbleSort(forSort, [](string a, string b) {	return a[a.length() - 1] > b[b.length() - 1]; });
	cout << endl;

	cout << "Sort by last element(smaller)\n";
	BubbleSort(forSort, [](string a, string b) {	return a[a.length()-1] < b[b.length()-1]; });
	cout << endl;

	cout << "Sort by length(smaller)\n";
	BubbleSort(forSort, [](string a, string b) {	return a.length() < b.length(); });
	cout << endl;

	cout << "Sort by length(greater)\n";
	BubbleSort(forSort, [](string a, string b){	return a.length() > b.length(); });
	cout << endl;

	system("pause");
	return 0;

}