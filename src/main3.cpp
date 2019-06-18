#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <ctime>
#include <random>

using namespace std;
mutex mu;


class  Customer
{
private:
    vector < int> items;
public:
    Customer()
    {
        int items_num = rand() % 15 + 1;
        for(int i = 0; i < items_num; i++ )
            items.push_back(rand()  % 100+1);
    }
    ~Customer(){}

    void addItem( int value)
    {
        items.push_back(value);
    }

    int getItemSize() const
    {
        return items.size();
    }


    void serve()
    {
        for(int i = 0; i < items.size(); i++ )
            this_thread::sleep_for(chrono::milliseconds(100));
        items.clear();
    }

};

void serve(queue<Customer*> cust)
{
    if (cust.empty())
        return;
    for (int i(1); !cust.empty(); i++)
    {
        mu.lock();
        cout << "tape id" <<  this_thread::get_id() << " customer items size "<<cust.front()->getItemSize() << endl ;
        mu.unlock();
        cust.front()->serve();
        cust.pop();
    }
}

int main()
{
    srand(0);
    queue<Customer*> customers;
    vector<thread*> threads;
    int custNum = 25;
    for (int i = 0; i < custNum; i++)
    {
        customers.push( new Customer());
        if ((customers.size() == 5) || (custNum - i < 5))
        {
            threads.push_back(new thread(serve, customers));
            while(!customers.empty())
                customers.pop();
        }
    }



    for (auto& th : threads)
        th->join();

    cout << "Market stat: " << custNum << " were served by market today" << endl;

}
