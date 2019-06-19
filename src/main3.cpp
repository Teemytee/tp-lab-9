#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <ctime>
#include <random>

using namespace std;
mutex mu;

void serve(queue<vector<int>> cust)
{
    for (int i(1); !cust.empty(); i++)
    {
        mu.lock();
        cout << "Checking customer with " << cust.front().size() << " goods on cashbox " << this_thread::get_id() << endl;
        mu.unlock();
        for (int j(0); j < cust.front().size(); j++)
        {
            this_thread::sleep_for(chrono::milliseconds(400));
        }
        cust.pop();
    }
}

int main()
{
    mt19937 gen(time(NULL));

    queue<vector<int>> customers;
    vector<thread*> threads;
    vector <int> goods;
    int customerNumber = gen() % 16, goodsNumber;
    cout << "We have " << customerNumber << " overall" << endl;

    for (int i(0); i < customerNumber; i++)
    {
        goodsNumber = 1 + gen() % 10;
        while (goodsNumber--)
        {
            int price = 1 + gen() % 500;
            goods.push_back(price);
        }
        customers.push(goods);
        goods.clear();
        if ((customers.size() % 5 == 0) || (i == customerNumber - 1))
        {
            threads.push_back(new thread(serve, customers));
            while(!customers.empty())
                customers.pop();
        }
    }
    for (auto& th : threads)
        th->join();

}

