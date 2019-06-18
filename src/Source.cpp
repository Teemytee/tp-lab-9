#include<iostream>
#include<thread>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include<queue>
#include<mutex>

using namespace std;

queue<queue<int>> TW1;
queue<queue<int>> TW2;
queue<queue<int>> TW3;
mutex Mu;

void WriteText(int NumCashBox, int NumFood)
{
	lock_guard<mutex> Lock(Mu);
	cout <<"CashBox["<< NumCashBox <<"]: Number of Food = "<< NumFood << endl;
}

void fun(queue<queue<int>>& TW, int id)
{
	while (true)
	{
		if (TW.empty())
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		while (!TW.empty())
		{
			while (!TW.front().empty())
			{
				this_thread::sleep_for(chrono::milliseconds(TW.front().front() * 100));
				WriteText(id, TW.front().size());
				TW.front().pop();
			}
			TW.pop();
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	thread tw1(fun, ref(TW1), 1);
	thread tw2(fun, ref(TW2), 2);
	thread tw3(fun, ref(TW3), 3);
	tw1.detach();
	tw2.detach();
	tw3.detach();
	
	while (true)
	{
		chrono::milliseconds Time_New_Customers = chrono::milliseconds(500 + rand() % 500);
		int CountFood = (1 + rand() % 5);
		this_thread::sleep_for(Time_New_Customers);
		queue<int> Goods;
		for (int i = 0; i < CountFood; ++i)
			Goods.push(1+rand()%15);

		if (TW1.size() < 5)
			TW1.push(Goods);
		else if (TW2.size() < 5)
			TW2.push(Goods);
		else 
			TW3.push(Goods);
	}
	
	system("Pause");
	return 0;
}