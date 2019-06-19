#include <iostream>
using namespace std;
#include <random>
#include <string>
#include<thread>
#include <mutex>
#define N 10
mutex mu;
mutex gla;
bool Flag;
bool stop;
int iteration = 0;
const char** BubbleSortT(const char* *mas, int n, function<bool(int, int)> f)
{
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++)
		{
			//Flag = false;
			if (f(strlen(mas[j]), strlen(mas[j + 1])))
			{
				mu.lock();
				const char* temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
				iteration++;
				Flag = true;
				mu.unlock();
				this_thread::sleep_for(chrono::seconds(1));
				Flag = false;
				
			}
		}
		
	}
	stop = true;
	return mas;
}

void PrintM(const char* *m)
{
	cout << iteration<<" ";
	for (auto i = 0; i < N; i++)
		cout << m[i] << " ";
	cout<<endl;
}
int main()
{
	stop = false;
	const char* cmas[] ={ "abc","defg","hijkl","mu","aaa","fsfsf","sdsd", "dada", "dwds", "dd" };

	thread t1(BubbleSortT,cmas, N, [](int a, int b) -> bool {return a > b ? true : false; });

	while (1) 
	{
		if (Flag == true)
		{
			mu.lock();
			PrintM(cmas);
			Flag = false;
			mu.unlock();
		}
		if (stop == true)
			break;
	}
	
	t1.join();
	cout << endl;
	system("pause");
	return 0;

}