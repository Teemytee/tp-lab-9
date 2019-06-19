#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

namespace myspace
{
	template<class A>
	auto lesser = [](A a, A b) { return a < b ? true : false; };

	template<class B>
	auto greater = [](B a, B b) { return a < b ? true : false; };

	template<class C, int bound>
	auto modSort = [](C a, C b) { return (a  % bound) > b ? true : false; };
}


mutex mu;
condition_variable cv;

bool sort_done = true;
bool print_done=false;

void tbody(int *pArray, size_t size, function<bool(int, int)> comparator)
{
	
	for (auto i = 0; i < size; ++i)
	{
		unique_lock<mutex> lock(mu);
		cv.wait(lock, []() {return print_done;});
		for (auto j = 0; j < size; ++j)
			if (!comparator(pArray[i], pArray[j]))
				swap(pArray[i], pArray[j]);


		sort_done = true;
		print_done = false;

		lock.unlock();
		cv.notify_all();
	}
	
}

int main()
{

	cout << endl << endl << "********** task #2 ***********" << endl << endl;

	size_t size = 10;
	int  arr[] = { 2,1,4,0,3,4,6,2,5,-11 };;
	auto *pArr = arr;
	
	cout << "unsorted array : " << endl;
	for (auto j = 0; j < size; ++j)
		cout << pArr[j] << " ";
	cout << endl;
	cout << endl;

	
	thread t(tbody, pArr, size, myspace::greater<int>);
	int i = size+1;
	while (i > 0)
	{
		unique_lock<mutex> lock(mu);
		cv.wait(lock, []() {return sort_done; });
		for (auto j = 0; j < size; ++j)
		{
			cout << pArr[j] << " ";
		}
		cout << endl;
		i--;

		sort_done = false;
		print_done = true;
		lock.unlock();
		cv.notify_all();
		
	}
	t.join();

	std::system("pause");
}