#include<iostream>
using namespace std;
#include<thread>
#include<mutex>
#include<vector>
#include <chrono>
#include<queue>
#include<ctime>
#include"Customer.h"
#define NUM 100
mutex mut;



void serve(Customer * cust)
{
	for (int i = 0; i < cust->products.size(); i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
	}

	{
		lock_guard<mutex> lock(mut);
		int tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		cout <<"Thread #"<<tid<<" "<< "Customer " << cust->id << " served" << endl;
	}
}
void kassa(queue<Customer*> q)
{
	while (!q.empty())
	{
		Customer * cust = q.front();
		serve(cust);
		q.pop();
	}

}

bool AllServed(vector<Customer*> &customers)
{
	for (int i = 0; i < customers.size(); i++)
	{
		if (customers[i]->served == false)
		{
			return false;
		}

	}
	return true;
}

int main() 
{
	int tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
	cout << "main thread: " << tid << endl;
	vector<Customer*> customers;

	vector<thread*> ts;

	for (int i = 0; i < NUM; i++)
	{
		customers.push_back(new Customer(i));
	}

	random_device ran;
	queue<Customer*> qu;
	while (1)
	{
			int moment = ran() % 100 + 1;
			int num = ran() % 5;
			for (int i = 0; i < num ; i++)
			{
				int j = ran() % customers.size();
				this_thread::sleep_for(chrono::milliseconds(moment));
				if (customers[j]->served==false && qu.size() < 5)
				{
					lock_guard<mutex> lock(mut);
					qu.push(customers[j]);
					customers[j]->served = true;
					cout << "Customer " << j << " arrived" << endl;
				}
			}

			if (qu.size() == 5)
			{
				ts.push_back(new thread(&kassa, qu));
				queue<Customer*> empty;
				swap(qu, empty);

			}

			if (!qu.empty())
			{
				Customer* cust = qu.front();
				serve(cust);
				qu.pop();
			}
			if (AllServed(customers))
				break;
	}

	for (auto &th : ts)
		th->join();
	system("pause");
	return 0;
}