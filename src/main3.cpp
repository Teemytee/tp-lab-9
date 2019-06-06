#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime> 

using namespace std;
mutex mu;

void producer(queue<vector<int>> qu) {
	lock_guard<mutex> lock(mu);
	cout << "Cashbox - " << this_thread::get_id() << endl;
	int i = 1;
	while (!qu.empty()) {
		cout << "consuming " << i << endl;
		for (int i = 0; i < qu.front().size(); i++) {
			this_thread::sleep_for(chrono::milliseconds(qu.front()[i] * 10));
		}
		qu.pop();
		i++;
	}
}

int main() {
	int numCust, k, m;
	queue<vector<int>> cust;
	vector<int> ran;
	vector<thread*> th;

	srand(time(NULL));
	numCust = 1 + rand() % 20;

	for (int i = 0; i < numCust; i++) {
		k = 1 + rand() % 9;
		for (int j = 0; j < k; j++) {
			m = 1 + rand() % 20;
			ran.push_back(m);
		}
		cust.push(ran);
		ran.clear();
		if ((i == numCust-1) || ((i + 1) % 5 == 0)) {
			th.push_back(new thread(producer, cust));
			while (!cust.empty()) cust.pop();
		}	
	}

	for (auto &t : th)
			t->join();

	cout << "finished!" << endl;
}