#include <iostream>
#include <random>
#include <string>
#include<thread>
#include <mutex>

using namespace std;

#define N 10
mutex mut;
bool flag, stop;
int iteration = 0;
const char** MySortT(const char* *mas, int n, function<bool(int, int)> f)
{
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++)
		{
			//flag = false;
			if (f(strlen(mas[j]), strlen(mas[j + 1])))
			{
				mut.lock(); //mutex' block
				const char* temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
				iteration++;
				flag = true;
				mut.unlock(); //mutex' free
				this_thread::sleep_for(chrono::seconds(1)); //pause for one second
				flag = false;

			}
		}

	}
	stop = true;
	return mas;
}

void PrintM(const char* *m)
{
	cout << iteration << " ";
	for (auto i = 0; i < N; i++)
		cout << m[i] << " ";
	cout << endl;
}
int main()
{
	stop = false;
	const char* MyMas[] = { "abc","defg","gtptf","tu","bbb","asasas","oppoo", "nono", "gajghj", "jj" };

	thread t1(MySortT, MyMas, N, [](int a, int b) -> bool {return a > b ? true : false; });

	while (1)
	{
		if (flag == true)
		{
			mut.lock();
			PrintM(MyMas);
			flag = false;
			mut.unlock();
		}
		if (stop == true)
			break;
	}

	t1.join(); //the end of the thread 
	cout << endl;
	system("pause");
	return 0;

}