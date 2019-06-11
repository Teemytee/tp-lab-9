#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>


template<typename T>
void bubble_sort(std::vector<T> &sequence, std::function<int(T, T)> comparator) {
    T tmp, switch_;
    int tmp_ind;
    for (unsigned int i = 0; i < sequence.size(); i++) {
        tmp_ind = 0;
        for (unsigned int j = 1; j < sequence.size() - i; j++) {
            if (comparator(sequence[j], sequence[tmp_ind]) == 1)
                tmp_ind = j;
        }
        switch_ = sequence[sequence.size()-1-i];
        sequence[sequence.size()-1-i] = sequence[tmp_ind];
        sequence[tmp_ind] = switch_;
    }
}


int main(int argc, char *argv[]) {
    std::vector<std::string> sequence{"lol", "KEK", "cheburek", "kek", "lol"};
    std::for_each(sequence.begin(), sequence.end(), [](std::string x){
        std::cout << x << " ";
    });
    std::cout << std::endl;
//
//    bubble_sort<std::string>(sequence, [](std::string a, std::string b){
//        return a > b;
//    });
//
//    bubble_sort<std::string>(sequence, [](std::string a, std::string b){
//        if (a.size() > 2 && b.size() > 2 && a[1] > b[1]) {
//            return 1;
//        } else {
//            return 0;
//        };
//    });
//
    bubble_sort<std::string>(sequence, [](std::string a, std::string b){
        if (a.size() > 2 && b.size() > 2 && a[1] > b[1]) {
            return 0;
        } else {
            return 1;
        };
    });
//
//    bubble_sort<std::string>(sequence, [](std::string a, std::string b){
//        if (a.size() >= b.size()) {
//            return 1;
//        } else {
//            return 0;
//        };
//    });

    std::for_each(sequence.begin(), sequence.end(), [](std::string x){
        std::cout << x << " ";
    });
    std::cout << std::endl;
    return EXIT_SUCCESS;
}