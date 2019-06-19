#include <iostream>
#include <functional>
#include <vector>
#include <string>

void sort(std::vector<std::string> words, std::function<bool(std::string, std::string)> cmp){
	for (int i = 0; i < words.size(); ++i) {
		for (int j = 0; j < words.size() - 1; ++j) {
			if (cmp(words[j], words[j + 1]))
				swap(words[j], words[j + 1]);
		}
	}

	for (int i = 0; i < words.size(); ++i)
		std::cout << words[i] << std::endl;
}

int main() {
	std::vector<std::string> words = { "kjasd", "kasfawd", "djhg", "ajwhdfjgbr", "hgtyxhzn", "sjh", "d" };
	sort(words, [](std::string a, std::string b) {return a.size() < b.size(); });
	sort(words, [](std::string a, std::string b) {return a.size() > b.size(); });
	sort(words, [](std::string a, std::string b) {return a > b; });					// по алфавит
	sort(words, [](std::string a, std::string b) {return a[0] > b[0]; });  
	system("pause");
}