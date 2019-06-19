// task2_Thread.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <functional>
#include <thread>
#include <string>
#include <mutex>
#include <iterator>
#include <condition_variable>
#define S 7

using namespace std;

mutex mutObj;
condition_variable_any th;
bool th1 = true;
bool th2 = false;

void bubbleSort(string *arr, function <bool(string a, string b)> cmp)
{
	for (int i = 0; i < S; i++)
	{
		lock_guard<mutex> guard(mutObj);
		th.wait(mutObj, []{ return th2; });
		for (int j = 0; j < S - (i + 1); j++)
		{
			if (cmp(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);
		}
		th1 = true; 
		th2 = false; 
		th.notify_all(); 
	}
}

int main()
{
 	string arr[S] = { "234r", "Sourse", "boys", "Distination", "cool", "trip", "amasing" };
	thread thread(bubbleSort, arr, [](string a, string b){ return a > b; });
	for (int i = 0; i < S; i++)
	{
		lock_guard<mutex> guard(mutObj); 
		th.wait(mutObj, [] { return th1; });
		for (int i = 0; i < S; i++) cout << arr[i] << " ";
		cout << endl;
		th1 = false; 
		th2 = true;
		th.notify_all(); 
	}
	thread.join();
}



