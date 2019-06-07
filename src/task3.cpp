#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <string>
using namespace std;


class  Customer
{
private:
	vector <int> goods;
public:
	Customer()
	{
		size_t n_goods = rand() % 30 + 1;
		while (n_goods > 0)
		{
			goods.push_back(rand()  % 150+1);
			n_goods--;
		}
	}
	void printCustGoods()
	{
		for (auto good : goods)
			cout << good<<" ";
		cout << endl<<endl;
		return;
	}
	void serveMe()
	{
		cout << goods.size()<<endl;
		for (auto good : goods)
				while(good>0)
					good--;
	}
	~Customer(){}
};

mutex mu;


void service(queue <Customer*> q)
{
	lock_guard<mutex> lock(mu);
	while (!q.empty())
	{
		Customer * customer = q.front();
		customer->serveMe();
		customer->~Customer();
		q.pop();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

class Market
{
private:
	vector < queue <Customer*>*> queues;
	vector<thread*> tapes;
public:
	Market()
	{
		queues.push_back(new queue<Customer*>);
	}
	void addNewCustomer(Customer * customer)
	{
		for (auto queue : queues)
		{
			if (queue->size() < 5)
			{
				queue->push(customer);
				return;
			}
		}
		queue<Customer*> * newQueue = new queue<Customer*>;
		newQueue->push(customer);
		runTape(*newQueue);
		queues.push_back(newQueue);
		return;
	}
	queue <Customer*>* getQueue()
	{
		return queues.back();
	}

	void runTape(queue <Customer*>  q)
	{
		tapes.push_back(new thread(service, q));
	}
	
	vector<thread*> getTapes()
	{
		return tapes;
	}
};




int main()
{
	Market mega;

	srand(time(nullptr));

	auto itr = 0;
	auto i = 0;
	while (1)
	{
		if (rand() % 10==0)
			mega.addNewCustomer(new Customer);
	}
	for (auto &t : mega.getTapes())
		t->join();
	std::system("pause");
}