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
		random_device rand; //generate random 
		this->id = id;
		this->served = false;
		int num = rand() % 10 + 1;

		for (int i = 0; i < num; i++)
		{
			products.push_back(rand() % 20);
		}
	}

};