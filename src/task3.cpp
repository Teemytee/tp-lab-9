#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

const int total_prod = 50;
mutex mu;

void kassa(queue < vector<int>> consumer) {
	for (int i = 1; i <= consumer.size(); i++) {
		mu.lock();
		cout << "work kassa number " << this_thread::get_id() << endl;
		mu.unlock();
		for (int j = 0; j < consumer.front().size(); j++) {
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		
	}
}

int main(){
	int total_cons; //всего купателей

	srand(time(nullptr));
	total_cons = rand() % 100;

	vector<int> prod; //кол-во продуктов
	queue < vector<int>> consumer; //очередь из покупателей с продуктами
	vector <thread*> kas; // набор касс


	cout << "Total people " << total_cons << endl;
	for (int i = 0; i < total_cons; i++) {
		int num_prod= rand() % total_prod; //кол-во продуктов покупателя
		for (int j = 0; j < num_prod; j++) { //заполнили продуктами
			int id_prod = rand() % total_prod; 
			prod.push_back(id_prod);
		}
		consumer.push(prod);
		prod.clear();
		
		int id = i;
		if ((consumer.size()==5)||(i+1==total_cons)) { //на 5 покупателе создаем кассу и на последних
			kas.push_back(new thread(kassa,consumer));
			while (!consumer.empty()) {
				consumer.pop();
			}
		}
	}
	for (auto &t : kas)
		t->join();
}