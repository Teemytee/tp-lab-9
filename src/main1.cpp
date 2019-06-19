#include <iostream>
#include <vector>
#include <ctime>
#include <string>

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
    for (int i = 0; i < array_size; i++) {
        bool flag = true;
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

    for (int i = 0; i < array_size; i++)
        cout<<array[i]<<" ";
    cout<<endl;
}
int main1() {
    srand(time(NULL));

    int array_size = 8;
    string* array = new string[array_size];
    initArray(array);

    bubbleSort(array, array_size, [](string a, string b){ return a<b; });
    bubbleSort(array, array_size, [](string a, string b){ return a>b; });
    bubbleSort(array, array_size, [](string a, string b){ return a!=b; });
    bubbleSort(array, array_size, [](string a, string b){ return a[0] > b[0];});
    bubbleSort(array, array_size, [](string a, string b)->bool{ string bound = "bound"; return a > bound;});

    delete[] array;
    return 0;
}