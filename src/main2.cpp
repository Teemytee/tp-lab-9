#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

void initArray(string* array)
{
    array[0] = "Absolutly";
    array[1] = "brilliant";
    array[2] = "boy";
    array[3] = "call";
    array[4] = "your";
    array[5] = "father";
    array[6] = "to";
    array[7] = "day";
}

typedef bool (func)(int a, int b);

void bubbleSort(string *array, int array_size, bool cmp(string a, string b))
{
    mutex outMutex;
    std::lock_guard<std::mutex> lockMutex(outMutex);
    for (int i = 0; i < array_size; i++) {
        bool flag = true;
        std::thread inThread([array_size](string* array){
            for (int i = 0; i < array_size; i++){
                cout<<array[i]<<" ";
            }
            std::cout << std::endl;
        }, array);
        inThread.join();

        for (int j = 0; j < array_size - (i + 1); j++) {

            if (cmp(array[j], array[j+1])) {
                flag = false;
                swap (array[j], array[j + 1]);
            }

        }
        if (flag) {
            break;
        }
    }
    
}
int main() {
    srand(time(NULL));

    int array_size = 8;
    string* array = new string[array_size];
    initArray(array);

    thread t(bubbleSort, array, array_size, [](string a, string b){return a<b;});
    t.join();

    delete[] array;
    return 0;
}
