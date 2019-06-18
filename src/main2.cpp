//
// Created by Alexander on 17.06.2019.
//

//
// Created by Alexander on 17.06.2019.
//
#include <cstring>
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


using namespace std;
mutex mtx;
condition_variable cond;
bool is_sorted, main_thread(true),bubble_thread(false);

void bubbleSort(int array_size,string array[],bool comparison(string first,string second))
{
    string temp = "";
    for (int i(0);i < array_size; ++i)
    {
        unique_lock<mutex> ul (mtx);
        cond.wait(ul,[](){return bubble_thread;});
        is_sorted = true;
        for (int int_counter = 0; int_counter < (array_size - i - 1); ++int_counter)
            if (comparison(array[int_counter],array[int_counter+1]))
            {
                temp = array[int_counter];
                array[int_counter] = array[int_counter + 1];
                array[int_counter + 1] = temp;
                is_sorted = false;
            }
        bubble_thread = false;
        main_thread = true;
        ul.unlock();
        cond.notify_one();
        if(is_sorted)
            break;


    }
}


int main (){
    auto start_time = Clock::now();
    string array[] = {"Simplicity","is","the","soul","of","the","efficiency"};
    int array_size = sizeof(array)/ sizeof(string);
    thread additional(bubbleSort,array_size,array,[](string a,string b){return a.length() < b.length();});

    while(true)
    {
        unique_lock<mutex> ul (mtx);
        cond.wait(ul,[](){return main_thread;});
        cout << "{";
        for (int i(0); i < array_size; i++) {
            cout << " " << array[i] << ", ";
        }
        cout << "}" << endl;
        main_thread = false;
        bubble_thread = true;
        ul.unlock();
        cond.notify_one();
        if(is_sorted)
            break;
    }
    additional.join();
    auto finish_time = Clock::now();
    cout << "Delta finish - start time: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time).count()
         << " milliseconds" << std::endl;
    return 0;
}