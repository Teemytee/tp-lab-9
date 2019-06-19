#include <iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>  
#include <mutex>
using namespace std;
const int num_people = 5;
const int max_num_items = 15;
const int max_num_people = 30;
mutex mu;
class Customer
{
private:
	vector<int>items;
public:
	Customer()
	{
		int num= rand() % max_num_items;
		for (int i = 0; i < num; i++)
			items.push_back(1);
	}
	void serve()
	{
		mu.lock();
		for(auto i:items)
			this_thread::sleep_for(chrono::seconds(1));
		print_about_service();
		items.clear();
		mu.unlock();
	}
	void print_about_service()
	{
		cout << "Customer with " << items.size() << " items was served by "<< this_thread::get_id()<<endl;
	}
};
void service(queue<Customer*>&cust)
{
	while(cust.size()!=0)
	{
		cust.front()->serve();
		if(cust.size() != 0) cust.pop();
	}
	
	
}
int main()
{
	srand(time(0));
	queue<Customer*> customers;
	vector<thread*> threads;
	int num = rand() % max_num_people;
	for (int i=0;i<num;i++)
	{
		int flag = rand() % 2;
		if (flag == 1)
		{
			customers.push(new Customer());
		}
		cout << customers.size() << endl;
		if (((customers.size())%num_people)==0)
		{
			threads.push_back(new thread(service, ref(customers)));
		}
	}
	for (auto i : threads)
		i->join();
	system("pause");
	return 0;
}