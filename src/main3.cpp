#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <ctime>
#include <thread>
#include <mutex>
#include <chrono>
#include <time.h>
using namespace std;

mutex mu;

void service(queue<vector<int>> cust_que) {//передаем копии
	while (!cust_que.empty()) {
		vector<int> c = cust_que.front();
		mu.lock();
		cout << cust_que.front().size() << " goods, " << "thread  " << this_thread::get_id() << endl;
		mu.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
		cust_que.pop();//фиктивно
	}
}

int main()
{
	srand(time(0));
	int n_cust = 9;
	queue<vector<int>> cust_que;
	vector<int> goods;
	vector<thread*> ts;
	for (int i = 0; i < n_cust; i++) {
		int n_goods = 2;
		for (int j = 0; j < n_goods; j++) {
			goods.push_back(rand() % 3 + 1);
		}
		cust_que.push(goods);
		goods.clear();
		if (cust_que.size() % 5 == 0 || i == n_cust - 1) {//очередь в 5 человек - запускаем обслуживание; если конец очереди, но 5-ти не набралось - запускаем обслуживание
			ts.push_back(new thread(service, cust_que));
			while (!cust_que.empty())//очищаем очередь реально
				cust_que.pop();
		}
	}
	for (auto &t : ts)
		t->join();
	//system("pause");
    return 0;
}