//
// Created by Alexander on 17.06.2019.
//
#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


using namespace std;
void bubbleSort(int array_size,string array[],bool comparison(string first,string second))
{
    string temp = "";
    bool is_sorted = false;

   for (int i(0);i < array_size; ++i)
   {
        is_sorted = true;
        for (int int_counter = 0; int_counter < (array_size - i - 1); ++int_counter)
            if (comparison(array[int_counter],array[int_counter+1]))
            {
                temp = array[int_counter];
                array[int_counter] = array[int_counter + 1];
                array[int_counter + 1] = temp;
                is_sorted = false;
            }
        if(is_sorted)
            break;
       cout << "{";
       for (int i(0); i < array_size; i++)
       {
           cout << " " << array[i] << ", ";
       }
       cout << "}" << endl;
   }
}


int main (){
    auto start_time = Clock::now();
    this_thread::sleep_for(chrono::seconds(2));
    string array[] = {"Simplicity","is","the","soul","of","the","efficiency"};
    int array_size = sizeof(array)/ sizeof(string);
//    cout << "1)\n";
//    bubbleSort(array_size,array,[](string a,string b){return a.length() > b.length();});
//    cout << "\n";
    cout << "2)\n";
    bubbleSort(array_size,array,[](string a,string b){return a.length() < b.length();});
    cout << "\n";
//    cout << "3)\n";
//    bubbleSort(array_size,array,[](string a,string b){return a[0] < b[0];});
//    cout << "\n";
//    cout << "4)\n";
//    bubbleSort(array_size,array,[](string a,string b){return a[0] > b[0];});
//    cout << "\n";
//    cout << "5)\n";
//    bubbleSort(array_size,array,[](string a,string b){return a < b;});
    auto finish_time = Clock::now();
    cout << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time - start_time).count()
              << " milliseconds" << std::endl;


}