#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>


template<typename T>
void bubble_sort(std::vector<T> *sequence, std::function<int(T, T)> comparator) {
    std::mutex output_mutex;

    T tmp, switch_;
    int tmp_ind;
    for (unsigned int i = 0; i < sequence->size(); i++) {
        std::thread inner_thread([&output_mutex](std::vector<T> *sequence){
            std::lock_guard<std::mutex> lock(output_mutex);
            std::for_each(sequence->begin(), sequence->end(), [](T &t) {
                std::cout << t << " ";
            });
            std::cout << std::endl;
            std::cout << std::endl;
        }, sequence);
        inner_thread.join();

        std::lock_guard<std::mutex> lock_(output_mutex);
        tmp_ind = 0;
        for (unsigned int j = 1; j < sequence->size() - i; j++) {
            if (comparator((*sequence)[j], (*sequence)[tmp_ind]) == 1)
                tmp_ind = j;
        }
        switch_ = (*sequence)[sequence->size()-1-i];
        (*sequence)[sequence->size()-1-i] = (*sequence)[tmp_ind];
        (*sequence)[tmp_ind] = switch_;
    }
}


void heil(const std::string &str) {
    std::cout << str << std::endl;
}


void ret_two(int *a) {
    *a += 1;
    std::cout << *a << std::endl;
}


int main(int argc, char *argv[]) {
    std::vector<std::string> sequence{"11", "1", "cheburek", "333", "5555"};
    std::for_each(sequence.begin(), sequence.end(), [](std::string x){
        std::cout << x << " ";
    });
    std::cout << std::endl;
    std::cout << std::endl;

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
//    bubble_sort<std::string>(sequence, [](std::string a, std::string b){
//        if (a.size() > 2 && b.size() > 2 && a[1] > b[1]) {
//            return 0;
//        } else {
//            return 1;
//        };
//    });
//

//    int a{0};
//    std::thread thread1(heil, "Hello");
//    thread1.join();
//    std::thread thread2(ret_two, &a);
//    thread2.join();
//    std::cout << a << std::endl;

    std::thread thread3(bubble_sort<std::string>, &sequence, [](std::string a, std::string b){
        if (a.size() >= b.size()) {
            return 1;
        } else {
            return 0;
        };
    });
    thread3.join();

    std::for_each(sequence.begin(), sequence.end(), [](std::string x){
        std::cout << x << " ";
    });
    std::cout << std::endl;


    return EXIT_SUCCESS;
}