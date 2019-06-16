#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
mutex mu;

void cleanQueue(queue<vector<int>>* consumers){
    while(!consumers->empty())
        consumers->pop();
}

void addToQueue(queue<vector<int>> *consumers,int numbOfGoods){
    vector<int> goods;
    for(int i = 0; i < numbOfGoods; i++){
        int randomCost = 1 + rand()%1000;
        goods.push_back(randomCost);
    }
    consumers->push(goods);
}


void till(queue<vector<int>> consumers){
    lock_guard<mutex> lock(mu);
    cout<<"till : "<<this_thread::get_id()<<" size "<<consumers.size()<<endl;
    while(!consumers.empty()){
        cout << "consuming " << endl;
        for(int i = 0; i < consumers.front().size(); i++){
            int randMilliSec = rand()%100;
            this_thread::sleep_for(chrono::milliseconds(randMilliSec));
        }
        consumers.pop();
    }
}


int main() {
    srand(time(NULL));

    int numbOfConsums = 5 + rand()%10;
    queue<vector<int>> consumers;
    vector<thread*> threads;

    while(numbOfConsums--){
        int numbOfGoods = 1 + rand()%5;

        addToQueue(&consumers, numbOfGoods);

        if ((consumers.size())%5 == 0){
            threads.push_back(new thread(till, consumers));
            cleanQueue(&consumers);
        }
    }

    for (auto &tread : threads)
        tread->join();

    return 0;
} 