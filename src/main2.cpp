#include <cstring>
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
#define SIZE 6
/* Написать программу, в которой для сортировки массива строк из 1 задачи применяется отдельный поток (std::thread).
 * Сортировка происходит во вспомогательном потоке, а основной поток выводит содержание массива после каждого шага
 * алгоритма. Потоки должны использовать мьютексы для синхронизации работы.*/

mutex mu;
condition_variable_any cv;

bool sort, mainth(true), addth(false);
void BubbleSort(string array[], bool cmp(string a, string b))
{
    int len = SIZE;

    for (int i(0); i < len; i++)
    {
        mu.lock();
        cv.wait(mu, []{return addth;});
        sort = true;
        for (int j(0); j < len - i - 1; j++)
        {
            if (cmp(array[j], array[j+1]))
            {
                sort = false;
                swap (array[j], array[j + 1]);
            }
        }
        mainth = true;
        addth = false;
        mu.unlock();
        cv.notify_all();
        if (sort)
            break;
    }

}



int main()
{
    string array[SIZE] = {"Hello", "darkness", "my", "old", "friend", "end"}; // Every time the order changes

    thread second(BubbleSort, array, [](string a, string b) {return a.length() < b.length();}); // length less
    while(true) // Основной поток
    {
        mu.lock();
        cv.wait(mu, [] {return mainth;});
        cout << "{";
        for (int i(0); i < SIZE; i++)
        {
            cout << " " << array[i] << ", ";
        }
        cout << "}" << endl;
        mainth = false;
        addth = true;
        mu.unlock();
        cv.notify_all();
        if (sort)
            break;
    }
    second.join();

    return 0;
}