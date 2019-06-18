#include <iostream>
#include <string>

using namespace std;

// ========== [Функция вывода содержимого массива на экран] ==========
void printArr(string *arr, int arr_len)
{
	for (int i = 0; i < arr_len; i++) cout << arr[i] << " ";
	cout << endl;
}

// ========== [Функция сортировки пузырьком] ==========
void bSort(string *arr, int arr_len, bool func(string str1, string str2))
{
	for (int i = 0; i < arr_len; i++)
	{
		for (int j = 0; j < arr_len - (i + 1); j++)
		{
			if (func(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);
		}
	}
}

int main()
{
	const short int ARR_LEN = 6; // длина массива
	string arr[ARR_LEN] = { "One", "two", "three", "four", "five", "six" };

	bSort(arr, ARR_LEN, [](string str1, string str2){ return str1[0] != str2[0]; });
	printArr(arr, ARR_LEN);

	bSort(arr, ARR_LEN, [](string str1, string str2){ return str1 > str2; });
	printArr(arr, ARR_LEN);

	bSort(arr, ARR_LEN, [](string str1, string str2){ return str1 < str2; });
	printArr(arr, ARR_LEN);

	bSort(arr, ARR_LEN, [](string str1, string str2){ return str1[1] > str2[1]; });
	printArr(arr, ARR_LEN);

	bSort(arr, ARR_LEN, [](string str1, string str2){ return str1[1] < str2[1]; });
	printArr(arr, ARR_LEN);

	return 0;
}