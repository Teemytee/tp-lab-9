#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include <functional>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex mx;
std::condition_variable cv;
const int delay = 10;
bool flag  = true;
bool sort  = true;
bool print = false;

template <typename T>
void bubblesort(T* arr, size_t size, std::function<bool(int,int)> comparator)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		
		for (size_t j = 0; j < size - i - 1; ++j)
		{
			std::unique_lock<std::mutex> lk(mx);
			cv.wait(lk, []() {return print; });
			
			if (comparator(arr[j], arr[j + 1]) == true)
			{
				std::swap<T>(arr[j], arr[j + 1]);
			}
			if (j == (size-i-2)) std::cout << std::endl;
			print = false;
			sort = true;
			cv.notify_all();
		}		
	}
	flag = false;
}

template <typename T>
auto greater = [](T a, T b)
{
	if (a > b)  return true;
	else		return false;
};


int main()
{
	int ints[] = { 9,8,7,6,5,4,3,2,1 };
	int* pints = ints;
	std::thread th(bubblesort<int>, pints, sizeof(ints) / sizeof(int), greater<int>);

	while (flag == true)
	{
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, []() {return sort; });
		for (const auto &elem : ints)
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
		print = true;
		sort = false;
		cv.notify_all();
	}

	th.join();
	system("pause");
	return 0;
}