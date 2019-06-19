#include <iostream>
using namespace std;
#include <functional>
#include <string>
#define N 10
const char** BubbleSort(const char* *mas, int n, function<bool(string, string)> f)
{
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++)
		{
			if (f(mas[j], mas[j + 1]))
			{
				const char* temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
	return mas;
}

int main() 
{
	const char* cmas[] = { "abc","defg","hijkl","mu","aaa","fsfsf","sdsd", "dada", "dwds", "dd" };

	const char** cmas1 = BubbleSort(cmas, N, [](string a, string b) -> bool {return a.length() > b.length() ? true : false; });

	for (int i = 0; i < N; i++)
	{
		cout << cmas1[i] << " ";
	}
	cout << endl;

	const char** cmas2 = BubbleSort(cmas, N, [](string a, string b) -> bool {return a.size() < b.size() ? true : false; });

	for (int i = 0; i < N; i++)
	{
		cout << cmas2[i] << " ";
	}
	cout << endl;

	const char** cmas3 = BubbleSort(cmas, N, [](string a, string b) -> bool {return a[0] > b[0] ? true : false; });

	for (int i = 0; i < N; i++)
	{
		cout << cmas3[i] << " ";
	}
	cout << endl;

	const char** cmas4 = BubbleSort(cmas, N, [](string a, string b) -> bool {return a.size() > b.size() ? true : false; });

	for (int i = 0; i < N; i++)
	{
		cout << cmas4[i] << " ";
	}
	cout << endl;

	const char** cmas5 = BubbleSort(cmas, N, [](string a, string b) -> bool {return a > b ? true : false; });

	for (int i = 0; i < N; i++)
	{
		cout << cmas5[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
