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
mutex mtx;

void shop(queue<vector<int>> q) {
	lock_guard<mutex> lock(mtx);
	cout << "Cashbox = " << this_thread::get_id() << endl;
	int i = 1;
	while (!q.empty()) {
		cout << "Shopper " << i << endl;
		for (int i = 0; i < q.front().size(); i++) {
			this_thread::sleep_for(chrono::milliseconds(q.front()[i]*20));
		}
		q.pop();
		i++;
	}
}

int main() {
	int NumberCust, purchase, timebuy;
	queue<vector<int>> cust;
	vector<int> vec;
	vector<thread*> th;

	srand(time(NULL));
	NumberCust = 1 + rand() % 50;
	cout << "Number Cust: " << NumberCust << endl;

	for (int i = 0; i < NumberCust; i++) {
		purchase = 1 + rand() % 20;
		for (int j = 0; j < purchase; j++) {
			timebuy = 1 + rand() % 20;
			vec.push_back(timebuy);
		}
		cust.push(vec);
		vec.clear();
		if ((i == NumberCust - 1) || ((i + 1) % 5 == 0)) {
			th.push_back(new thread(shop, cust));
			while (!cust.empty()) cust.pop();
		}
	}

	for (auto &t : th)
		t->join();

	cout << "finished!" << endl;
	system("pause");
}