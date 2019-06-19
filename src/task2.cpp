#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mut;
bool flag, stop = true;
int counter = 0;


void sort(std::vector<std::string>& words, std::function<bool(std::string, std::string)> cmp) {
	for (int i = 0; i < words.size(); ++i) {
		for (int j = 0; j < words.size() - 1; ++j) {
			if (cmp(words[j], words[j + 1])) {
				mut.lock();
				swap(words[j], words[j + 1]);
				++counter;
				flag = true;
				mut.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				flag = false;
			}
				
		}
	}
	stop = false;
	
}

int main() {
	std::vector<std::string> words = { "kjasd", "kasfawd", "djhg", "ajwhdfjgbr", "hgtyxhzn", "sjh", "d" };
	//sort(words, [](std::string a, std::string b) {return a.size() < b.size(); });
	
	std::thread th(sort, std::ref(words), [](std::string a, std::string b) {return a.size() < b.size();});

	while (stop) {
		if (flag == true) {
			mut.lock();
			std::cout << "iter :" << counter << std::endl;

			for (int i = 0; i < words.size(); ++i) {
				std::cout<< words[i] << std::endl;
			}

			flag = false;
			mut.unlock();
		}
	}

	th.join();
	system("pause");
	return 0;
}