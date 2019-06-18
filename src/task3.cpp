#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include <chrono>
#include<queue>
#include<ctime>
#include"header.h"

using namespace std;


#define NUM 100
mutex mute;



void serve(Customer * custom)
{
	for (int i = 0; i < custom->products.size(); i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
	}

	{
		lock_guard<mutex> lock(mute);
		int tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		cout << "Thread #" << tid << " " << "Customer " << custom->id << " served" << endl;
	}
}

void cash_register(queue<Customer*> q)//first-in - first-out
{
	while (!q.empty())
	{
		Customer * custom = q.front(); //call the first element
		serve(custom);
		q.pop(); //delete the first element 
	}

}

bool All_Customers_Served(vector<Customer*> &customers)
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
	cout << "The main thread: " << tid << endl;
	vector<Customer*> customers;

	vector<thread*> ts;

	for (int i = 0; i < NUM; i++)
	{
		customers.push_back(new Customer(i)); //+new element at the end of the vector
	}

	random_device rand;
	queue<Customer*> qu;
	while (1)
	{
		int moment = rand() % 100 + 1;
		int num = rand() % 5;
		for (int i = 0; i < num; i++)
		{
			int j = rand() % customers.size();
			this_thread::sleep_for(chrono::milliseconds(moment));
			if (customers[j]->served == false && qu.size() < 5)
			{
				lock_guard<mutex> lock(mute);
				qu.push(customers[j]);
				customers[j]->served = true;
				cout << "Customer " << j << " arrived" << endl;
			}
		}

		if (qu.size() == 5)
		{
			ts.push_back(new thread(&cash_register, qu));
			queue<Customer*> empty;
			swap(qu, empty); //change places

		}

		if (!qu.empty())
		{
			Customer* cust = qu.front();
			serve(cust);
			qu.pop();
		}
		if (All_Customers_Served(customers))
			break;
	}

	for (auto &th : ts)
		th->join(); //the end of the thread 
	system("pause");
	return 0;
}