#include <iostream>
#include <functional>
#include <string>

using namespace std;

#define N 10
const char** MySort(const char* *mas, int n, function<bool(string, string)> f) //algorithm Bubble Sort
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

int main(){
	const char* MyMas[] = { "abc","defg","gtptf","tu","bbb","asasas","oppoo", "nono", "gajghj", "jj" };

	const char** MyMas1 = MySort(MyMas, N, [](string cur, string prev) -> bool {return cur.length() > prev.length() ? true : false; }); //[](list with parametrs)->function' body 																																	//sort by string' length (from max to min)
	for (int i = 0; i < N; i++)                                                                                                         //sort by length (from min to max)
	{
		cout << MyMas[i] << " ";
	}
	cout << endl;


	const char** MyMas2 = MySort(MyMas, N, [](string cur, string prev) -> bool {return cur > prev ? true : false; }); //sort by alphabet
	for (int i = 0; i < N; i++)
	{
		cout << MyMas2[i] << " ";
	}
	cout << endl;


	const char** MyMas3 = MySort(MyMas, N, [](string cur, string prev) -> bool {return cur[0] > prev[0] ? true : false; }); //sort by first symbol
	for (int i = 0; i < N; i++)
	{
		cout << MyMas3[i] << " ";
	}
	cout << endl;


	const char** MyMas4 = MySort(MyMas, N, [](string cur, string prev) -> bool {return cur.size() > prev.size() ? true : false; }); //sort by string' size (from min to max)
	for (int i = 0; i < N; i++)
	{
		cout << MyMas4[i] << " ";
	}
	cout << endl;


	const char** MyMas5 = MySort(MyMas, N, [](string cur, string prev) -> bool {return cur.size() < prev.size() ? true : false; }); //sort by string' size (from max to min)
	for (int i = 0; i < N; i++)
	{
		cout << MyMas5[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}