#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <thread>
#include <mutex>

using namespace std;


template<typename T>
void bubble_sort(vector<T> *vec, function<bool(T, T)> comparator) {
    if (vec->empty())
        return;
    mutex output_mutex;
    lock_guard<mutex> lock(output_mutex);
    bool isSorted = true;
    int k =0;
    for(int i = 0; i < vec->size(); i++) {
        thread out_thread([&output_mutex,&k](vector<T> *vec){
            for_each((*vec).begin(), (*vec).end(), [](T x){ cout << x << " ";});
            cout << "  " << k <<"-th iteration" << endl;
            k++;
        }, vec);
        out_thread.join();

        for (int j = 0; j < (*vec).size() - i - 1; j++) {
            if (comparator((*vec)[j], (*vec)[j+1])) {
                swap((*vec)[j], (*vec)[j+1]);
                isSorted = false;
            }
        }
        if (isSorted)
            return;
    }
}


int main() {
    vector<string> vec{"a", "aa", "aaa", "aaaa", "aaaaa"};
    cout << "Source vector : ";
    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;
    cout << "Sorting by string cmp up down : ";


    thread thread1(bubble_sort<string>, &vec, [](string a, string b){
        if (a<b)
            return true;
        else
            return false;
    });
    thread1.join();

    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;

/*
    cout << "Sorting by string cmp down up : ";
    bubble_sort<string>(vec, [](string a, string b){
        if (a>b)
            return true;
        else
            return false;
    });


    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;

    cout << "addition of 1 element in vec:  ";
    vec.push_back("bb");

    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;


    cout << "Sorting by strlen down up : ";
    bubble_sort<string>(vec, [](string a, string b){
        if (a.length()>b.length())
            return true;
        else
            return false;
    });

    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;


    cout << "Sorting by strlen up down : ";
    bubble_sort<string>(vec, [](string a, string b){
        if (a.length()<b.length())
            return true;
        else
            return false;
    });
    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;



    cout << "Sorting by first chars up down : ";
    bubble_sort<string>(vec, [](string a, string b){
        if (a[0]<b[0])
            return true;
        else
            return false;
    });
    for_each(vec.begin(), vec.end(), [](string x){ cout << x << " ";});
    cout << endl;

*/

    return 0;
}

