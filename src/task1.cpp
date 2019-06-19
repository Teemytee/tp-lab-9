#include <iostream>
#include <algorithm>

template <typename T, typename F>
void bubblesort(T* arr, size_t size, const F &comparator)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = 0; j < size - i - 1; ++j)
		{
			if (comparator(arr[j], arr[j + 1]) == true)
			{
				std::swap<T>(arr[j], arr[j + 1]);
			}
		}
	}
}

template <typename T, int num>
auto modgreater = [](T a, T b)
{
	if (a%num > b%num)  return true;
	else				return false;
};
template <typename T>
auto greater = [](T a, T b)
{
	if (a > b)  return true;
	else		return false;
};
template <typename T>
auto lesser = [](T a, T b)
{
	if (a < b)  return true;
	else		return false;
};
template <typename T>
auto lengreater = [](T a, T b)
{
	if (strlen(a) > strlen(b))  return true;
	else						return false;
};
template <typename T>
auto lenlesser = [](T a, T b)
{
	if (strlen(a) < strlen(b))  return true;
	else						return false;
};


int main()
{

	int ints1[5] = { 4,5,3,2,1 };
	int ints2[5] = { 4,5,3,2,1 };
	int ints3[9] = { 4,5,1,2,1,2,2,2,0 };

	bubblesort(ints1, 5, [](int a, int b)
	{
		if (a%2 > b%2)  return true;
		else				return false;
	});
	for (const auto &elem : ints1)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	bubblesort(ints2, 5, lesser<int>);
	for (const auto &elem : ints2)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	bubblesort(ints3, 9, modgreater<int, 2>);
	for (const auto &elem : ints3)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	char* char1[5] = {(char*)"55555", (char*)"4444", (char*)"333", (char*)"22", (char*)"1"};
	char* char2[5] = { (char*)"1", (char*)"22", (char*)"333", (char*)"4444", (char*)"55555" };
	
	bubblesort(char1, 5, lengreater<char*>);
	for (const auto &elem : char1)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	bubblesort(char2, 5, lenlesser<char*>);
	for (const auto &elem : char2)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}