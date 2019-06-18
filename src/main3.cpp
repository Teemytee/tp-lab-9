#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <ctime>
#include <random>
using namespace std;
mutex mutex1;

void service(queue<vector<int>> customers)
{
    for(int i(1);!customers.empty();i++)
    {
        mutex1.lock();
        cout << "Serving customer, which has " << customers.front().size() << " products"
        << " by " << this_thread::get_id() << "thread"<<endl;
        mutex1.unlock();
        for(int j(0);j <customers.front().size();j++ ){
            this_thread::sleep_for(chrono::seconds(2));
        }
        customers.pop();

    }

}


int main() {
    srand(time(NULL));


    queue<vector<int>> customers;
    vector<thread*> threads_vec;
    vector<int> products;

    int customers_amount = rand() % 20;
    int products_number;
    cout << customers_amount << "cuctomers"<<endl;


    for (int i(0); i < customers_amount; i++)
    {
        products_number = 1 + rand() % 15;
        for (int i(1);i <= products_number;++i)
        {
            products.push_back(i); // add products index to the vector
        }
        customers.push(products);
        products.clear();
        if ((customers.size() % 5 == 0) || (i == customers_amount - 1))
        {
            threads_vec.push_back(new thread(service,customers));
            while(!customers.empty())
                customers.pop();
        }


    }
    for(auto &th :threads_vec)
        th->join();



}