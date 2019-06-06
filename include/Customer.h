#pragma once
#include<iostream>
#include<vector>
#include<random>
using namespace std;

class Customer
{
public:
	vector<int> products;
	int id;
	bool served;

	Customer(int id)
	{
		random_device ran;
		this->id = id;
		this->served = false;
		int num = ran() % 10 + 1;

		for (int i = 0; i < num; i++)
		{
			products.push_back(ran() % 20);
		}
	}

};
