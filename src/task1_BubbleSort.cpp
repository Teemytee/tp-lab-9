// task1_BubbleSort.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <array>
#include <string>
#include <functional>
#define S 7
using namespace std;

void bubbleSort(array <string ,S> &arr, function <bool(string a, string b)> cmp)
{

	for (int i = 0; i < arr.size() - 1; i++)
	{
		for (int j = (arr.size() - 1); j > i; j--) 
		{
			if (cmp(arr[j - 1], arr[j]))
			{
				swap(arr[j - 1], arr[j]);
			}
		}
	}
}

int main()
{
	array <string, S> mas = { "234r", "Sourse", "boys", "Distination", "cool", "trip", "amasing" };
	//first sort length of mas 
	bubbleSort(mas, [](string a, string b) {return a.length() < b.length(); });
	//second sort length of mas 
	bubbleSort(mas, [](string a, string b) {return a.length() > b.length(); });
	//first alphabetical sort
	bubbleSort(mas, [](string a, string b) {return a < b; });
	//second alphabetical sort
	bubbleSort(mas, [](string a, string b) {return a > b; });
	//last simbol sorting
	bubbleSort(mas, [](string a, string b) {return a[a.length() - 1] > b[b.length()-1]; });
}

