#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

bool endS = false, 
	 th1 = true, 
	 th2 = false;
mutex mu;
condition_variable cv;

void sortBub(vector<string>* vec, const function<bool(string, string)> fun) {
	int n = (*vec).size();
	if (n == 0) return;
	int i = 0;
	char swap_cnt = 0;

	while (i < n)
	{
		unique_lock<mutex> lock(mu);
		cv.wait(lock, [] {return th2; });

		cout << "Sort procces" << endl;
		if (i + 1 != n && fun((*vec)[i], (*vec)[i + 1]) == 0)
		{
			swap((*vec)[i], (*vec)[i + 1]);
			swap_cnt = 1;
		}
		i++;
		if (i == n && swap_cnt == 1)
		{
			swap_cnt = 0;
			i = 0;
		}

		th1 = true;
		th2 = false;
		lock.unlock();
		cv.notify_all();
	}
	endS = true;
}

int main()
{
	vector<string> v = { "fffff", "bf", "ba", "a", "vvv", "zlkasl", "kkk" };

	
	//thread thS(func, 5);
	thread thS(sortBub, &v, [](string a, string b) {return a <= b; });
	while (true)
	{
		unique_lock<mutex> lk(mu);
		cv.wait(lk, [] {return th1; });

		copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
		if (endS) break;

		th2 = true;
		th1 = false;
		lk.unlock();
		cv.notify_all();
	}
	thS.join();
}

