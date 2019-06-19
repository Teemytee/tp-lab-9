#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
#define N 5

mutex mu;
condition_variable cv;
bool mainFinished = false;
bool bubbleFinished = true;
bool flag = true;

void bubbleSort(string** str, bool Comparator(string, string)) {
	for (int i = 0; i < N; i++) {
		unique_lock<mutex> lk(mu);//захватили мьютекс
		cv.wait(lk, []() {return mainFinished; });//ставит поток в ожидание сигнала - выход из ожидания выполнение печати (mainThread = true)
		for (int j = 0; j < N - i - 1; j++) {
			if (Comparator((*str)[j], (*str)[j + 1])) {
				swap((*str)[j], (*str)[j + 1]);
			}
		}
		bubbleFinished = true;//обновляем условия
		mainFinished = false;
		lk.unlock();//разблокировали мьютекс
		cv.notify_all();//разблокирует все потоки ожидающие на данном объекте condition_variable
	}
	flag = false;
}

int main()
{
	string str[N] = { "Lupa Lupova-Lupeeva", "Pupa Pa", "Kepa Kepovna", "Mepa Mepeeva", "Feta Fetovna" };
	string** ptr = new string*[N];
	for (int i = 0; i < N; i++) {
		ptr[i] = str + i;
	}
	//int n = sizeof(str)/sizeof(str[0]);
	auto Comparator = [](string str1, string str2) {return str1 > str2 ? true : false; };
	thread t(bubbleSort, ptr, Comparator);
	while (flag) {
		unique_lock<mutex>lk(mu);
		cv.wait(lk, []() {return bubbleFinished; });
		for (string s : str) cout << s << endl;
		cout << endl;
		mainFinished = true;
		bubbleFinished = false;
		lk.unlock();
		cv.notify_all();
	}
	t.join();
	//system("pause");
	return 0;
}