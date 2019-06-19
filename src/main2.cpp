#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// ========== [Глобальные объекты для манипуляции с потоками] ==========
mutex mutObj;
condition_variable_any thread_access;

bool main_thread_access = true;
bool addit_thread_access = false;

// ========== [Функция вывода содержимого массива на экран] ==========
void printArr(string *arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++) cout << arr[i] << " ";
	cout << endl;
}

// ========== [Функция сортировки пузырьком] ==========
void bubbleSort(string *arr, int array_size, bool func(string a, string b))
{
	for (int i = 0; i < array_size; i++)
	{
		lock_guard<mutex> guard(mutObj); // блокируем выполнение других потоков
		// если доступ к выполнению вспомогательного потока = true, то мы "дождались" выполнения этого кода
		thread_access.wait(mutObj, []{ return addit_thread_access; });
		
		// то выполним действия этой функции (а иначе позволим выполнятся основному потоку)

		for (int j = 0; j < array_size - (i + 1); j++)
		{
			if (func(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);	
		}

		main_thread_access = true; // в любом случае, после выполнения кода выше, разрешим доступ к выполнению основного потока 
		addit_thread_access = false; // а к вспомогательному запретим

		thread_access.notify_all(); // "оповестим" переменные об их изменении
	}
}

int main()
{
	const short int ARR_LEN = 6; // длина массива
	string arr[ARR_LEN] = { "One", "two", "three", "four", "five", "six" };

	// запустим выполнение вспомогательного потока
	thread addit_thread(bubbleSort, arr, ARR_LEN, [](string a, string b){ return a > b; });
	
	for (int i = 0; i < ARR_LEN; i++)
	{
		cout << "\t[" << i << "]" << endl;
		
		lock_guard<mutex> guard(mutObj); // блокируем выполнение других потоков

		// если доступ к выполнению основного потока = true, то мы "дождались" выполнения этого кода
		thread_access.wait(mutObj, [] { return main_thread_access; });

		printArr(arr, ARR_LEN); // выведем значение массива на экран
		
		main_thread_access = false; // запретим доступ к выполнению основного потока 
		addit_thread_access = true; // разрешим доступ к выполнению вспомогательного потока 

		thread_access.notify_all(); // "оповестим" переменные об их изменении
	}

	addit_thread.join(); // дождемся завершения вспомогательного потока

	return 0; // программа завершена.
}