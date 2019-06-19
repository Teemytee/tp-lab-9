#include <iostream>
#include <thread>
#include <deque>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>

class CCustomer
{
public:
	CCustomer()
	{
		for (int i = 0; i < 1 + rand() % 10; ++i)
		{
			Cart.push_back(0);
		}
	}
private:
	std::vector<int> Cart;
};

class CShop
{
public:
	CShop()
	{
		Lines.push_back(new std::deque<CCustomer*>);
	}
	void NewCustomer(CCustomer* customer)
	{
		for (auto it = Lines.begin(), end = Lines.end();; ++it)
		{
			if ((*it)->size() < 5)
			{
				(*it)->push_back(customer);
				break;
			}
			if (it == end)
			{
				Lines.push_back(new std::deque<CCustomer*>);
				Lines.back()->push_back(customer);
			}
		}
	}
private:
	std::vector<std::deque<CCustomer*>*> Lines;
	std::vector<std::thread> Threads;
};

int main()
{
	srand(time(NULL));
	CShop shop;
	while (1)
	{
		if (rand() % 10 == 0)
		{
			shop.NewCustomer(new CCustomer());
		}
	}

	return 0;
}