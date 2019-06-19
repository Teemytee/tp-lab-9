#include <iostream>
#include <vector>
#include<string>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;
condition_variable cond_var;
mutex mu;
bool print_done=false;
bool sort_done=true;
bool getSort = false;
void BubbleSort(vector<string>&myVec, bool cmp(string a, string b))
{
	
	for (int i = 0; i < myVec.size(); i++)
	{
		unique_lock<mutex> lock(mu);
		cond_var.wait(lock, []() {return print_done; });
		for (int j = 0; j < myVec.size() - 1; j++)
		{
			
			if (cmp(myVec[j], myVec[j + 1]))
				swap(myVec[j], myVec[j + 1]);
			
		}
		sort_done = true;
		print_done = false;
		lock.unlock();
		cond_var.notify_all();
	}
	getSort = true;
}

int main()
{
	vector<string>forSort = { "Zyxwp","Abc","LMNBHJ","18uhgsp","0008","qwertyyy" };
	thread t(BubbleSort , ref(forSort), [](string a, string b) {return a.length() > b.length(); });
	while (!getSort)
	{
		unique_lock<mutex> lock(mu);
		cond_var.wait(lock, []() {return sort_done; });
		for (auto i :forSort)
			cout << i << " ";
		cout << endl;
		sort_done = false;
		print_done = true;
		lock.unlock();
		cond_var.notify_all();
	}
	t.join();
	system("pause");
	return 0;

}