
#include <cstring>
#include <functional>
#include <iostream>

using namespace std;

#define SIZE 6
//typedef bool (func)(int a, int b);

void BubbleSort(string array[], bool cmp(string a, string b))
{
    int len = SIZE;
    bool sort;
    for (int i(0); i < len; i++)
    {
        sort = true;
        for (int j(0); j < len - i - 1; j++)
        {
            if (cmp(array[j], array[j+1]))
            {
                sort = false;
                swap (array[j], array[j + 1]);
            }
        }
        if (sort)
        break;
    }

    cout << "{";
    for (int i(0); i < len; i++)
    {
        cout << " " << array[i] << ", ";
    }
    cout << "}" << endl;
}


int main()
{
    string array[SIZE] = {"Hello", "darkness", "my", "old", "friend", "end"}; // Every time the order changes
    BubbleSort(array, [](string a, string b) {return a.length() < b.length();}); // length less
    BubbleSort(array, [](string a, string b) {return a.length() > b.length();}); //great
    BubbleSort(array, [](string a, string b) {return a != b;}); //Do not match
    BubbleSort(array, [](string a, string b) {return a[0] < b[0];}); // First char a less
    BubbleSort(array, [](string a, string b) {return a[0] < b[0];});
    BubbleSort(array, [](string a, string b) {return a > b;});
    return 0;
}