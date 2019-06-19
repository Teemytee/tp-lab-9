#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <mutex>
#include <iterator>
#include <condition_variable>

using namespace std;

mutex mu;
bool th1 = true;
bool th2 = false;
bool stop = false;
condition_variable cv;

 void sort(vector<string>* mas, const function<bool(string, string)> f) { 
	vector<string>& ma = *mas;

	for (int i = mas->size() - 1; i >= 1; i--) {
		for (int i = 0; i < mas->size(); i++) {
			if ((i + 1 != mas->size()) && (f(ma[i], ma[i + 1])==0)) {
				unique_lock<mutex> lock(mu);
				cv.wait(lock, [] {return th2; });

				string tmp = ma[i];
				ma[i] = ma[i + 1];
				ma[i + 1] = tmp;

				th1 = true;
				th2 = false;
				lock.unlock();
				cv.notify_all();
			}
		}
	}
	stop = true;
 }

int main()
{
	vector <string> mas = { "Vincent","Sabrina","Donna","Ethan","Christopher","John","Joleen","Hillary","James" };

	cout << "Sorting array by word length (ascending)" << endl;
	thread sorting_thread(sort, &mas, [](string a, string b) {return a.length() < b.length(); });

	while (1)
	{
		unique_lock<mutex> lk(mu);
		cv.wait(lk, [] {return th1; });

		copy(mas.begin(), mas.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
			
		if (stop) break;

		th2 = true;
		th1 = false;
		lk.unlock();
		cv.notify_all();
	}

	sorting_thread.join();
}