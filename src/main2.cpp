#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// ========== [���������� ������� ��� ����������� � ��������] ==========
mutex mutObj;
condition_variable_any thread_access;

bool main_thread_access = true;
bool addit_thread_access = false;

// ========== [������� ������ ����������� ������� �� �����] ==========
void printArr(string *arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++) cout << arr[i] << " ";
	cout << endl;
}

// ========== [������� ���������� ���������] ==========
void bubbleSort(string *arr, int array_size, bool func(string a, string b))
{
	for (int i = 0; i < array_size; i++)
	{
		lock_guard<mutex> guard(mutObj); // ��������� ���������� ������ �������
		// ���� ������ � ���������� ���������������� ������ = true, �� �� "���������" ���������� ����� ����
		thread_access.wait(mutObj, []{ return addit_thread_access; });
		
		// �� �������� �������� ���� ������� (� ����� �������� ���������� ��������� ������)

		for (int j = 0; j < array_size - (i + 1); j++)
		{
			if (func(arr[j], arr[j + 1]))
				swap(arr[j], arr[j + 1]);	
		}

		main_thread_access = true; // � ����� ������, ����� ���������� ���� ����, �������� ������ � ���������� ��������� ������ 
		addit_thread_access = false; // � � ���������������� ��������

		thread_access.notify_all(); // "���������" ���������� �� �� ���������
	}
}

int main()
{
	const short int ARR_LEN = 6; // ����� �������
	string arr[ARR_LEN] = { "One", "two", "three", "four", "five", "six" };

	// �������� ���������� ���������������� ������
	thread addit_thread(bubbleSort, arr, ARR_LEN, [](string a, string b){ return a > b; });
	
	for (int i = 0; i < ARR_LEN; i++)
	{
		cout << "\t[" << i << "]" << endl;
		
		lock_guard<mutex> guard(mutObj); // ��������� ���������� ������ �������

		// ���� ������ � ���������� ��������� ������ = true, �� �� "���������" ���������� ����� ����
		thread_access.wait(mutObj, [] { return main_thread_access; });

		printArr(arr, ARR_LEN); // ������� �������� ������� �� �����
		
		main_thread_access = false; // �������� ������ � ���������� ��������� ������ 
		addit_thread_access = true; // �������� ������ � ���������� ���������������� ������ 

		thread_access.notify_all(); // "���������" ���������� �� �� ���������
	}

	addit_thread.join(); // �������� ���������� ���������������� ������

	return 0; // ��������� ���������.
}