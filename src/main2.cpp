#include <mutex>
#include <thread>
#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <condition_variable>


using namespace std;
condition_variable_any cv;


mutex mut;
bool stop = 1;
bool mainth = true;
bool secthr = false;

void BSort(vector<string> &vec, bool cmp(string a, string b)) {
	int len = vec.size();

	for (int i = 0; i < len; i++) {
		
		for (int j = 0; j < len - 1; j++) {
			mut.lock();
			cv.wait(mut, [] {return secthr; });
			
			if (cmp(vec[j], vec[j + 1])) {
				swap(vec[j], vec[j + 1]);
			}
			mut.unlock();
			mainth = true;
			secthr = false;
			cv.notify_all();
		}
		
		//this_thread::yield();
	}
	stop = 0;
}



int main() {

	vector<string> a = { "a", "bb", "ccc", "dddd", "eeeeee", "fffffff" };
	thread tr1 (BSort, ref(a), [](string a, string b) {return a.size() < b.size(); });
		

	while (stop) {
		mut.lock();
		cv.wait(mut, [] {return mainth; });
		for_each(a.begin(), a.end(), [](string x) { cout << x << " "; });
		cout << endl;
		mainth = false;
		secthr = true;
		mut.unlock();
		cv.notify_all();
	}

	tr1.join();
	getchar();
}