#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable condition;
bool finish(false);
bool print(false);
bool process(true);


void Buble(vector<string>* v, function<bool(string, string)> function)
{
	int SizeVector = v->size();
	vector<string>& vec = *v;
	string tmp;
	bool sorting = true;
	for (int i = 0; i < SizeVector && sorting; i++)
	{
		unique_lock<mutex> lock(mtx);
		condition.wait(lock, [] {return (print); });

		sorting = false;
		for (int j = 0; j < (SizeVector - i - 1); j++)
		{
			if (function(vec[j], vec[j + 1]))
			{
				tmp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = tmp;
				sorting = true;
			}
		}

		process = true;
		print = false;
		cout << "end" << endl;
		lock.unlock();
		condition.notify_all();
	}
	finish = true;
}

int main()
{
	vector<string> VectorString = { "Red","Orange","Yellow", "Green", "Aqua", "Blue", "Purple" };
	thread t(Buble, &VectorString,
		[](string First, string Second) {return (First.size()<Second.size()); });
	while (1)
	{
		unique_lock<mutex> lock(mtx);
		condition.wait(lock, [] {return (process); });
		if (finish)
		{
			cout << "finish sorting" << endl;
			break;
		}
		process = false;
		for_each(VectorString.begin(), VectorString.end(), [](string s) {cout << s << " "; });
		cout << endl;
		print = true;
		lock.unlock();
		condition.notify_all();
	}
	t.join();
	system("pause");
}