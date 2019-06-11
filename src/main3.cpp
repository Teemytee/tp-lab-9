#include <vector>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>


void one_queue(std::vector<std::vector<int>*> *line, std::vector<std::thread::id> *threads_ids, std::mutex *mutex) {
    std::unique_lock<std::mutex> threads_ids_lock(*mutex);
    threads_ids->emplace_back(std::this_thread::get_id());
    threads_ids_lock.unlock();
    std::for_each(line->begin(), line->end(), [](std::vector<int>* client){
        std::cout << "queue #" << std::this_thread::get_id() << " served client " << (*client)[0] << std::endl;
//        std::for_each(client->begin(), client->end(), [](int i){
//            std::cout << "queue #" << std::this_thread::get_id() << " has served another client's product " << i << std::endl;
//            usleep(500000);
//        });
        usleep(1000000);
    });
    std::thread::id this_id = std::this_thread::get_id();
    threads_ids_lock.lock();
    for (size_t i = 0; i < threads_ids->size(); i++) {
        if ((*threads_ids)[i] == this_id) {
            threads_ids->erase(threads_ids->begin() + i);
        }
    }
    threads_ids_lock.unlock();
    delete line;
}


void push_clients(std::vector<std::vector<int>> *clients, std::queue<std::vector<int>*> *queue, std::mutex *mutex) {
    std::unique_lock<std::mutex> input_lock(*mutex, std::defer_lock);
    std::for_each(clients->begin(), clients->end(), [&queue, &input_lock](std::vector<int> &client){
        usleep(500000);
        input_lock.lock();
        queue->push(&client);
        input_lock.unlock();
        std::cout << "pushed new client " << client[0] << std::endl;
    });
}


int main(int argc, char *argv[]) {

    std::vector<std::vector<int>> clients;
    std::queue<std::vector<int>*> queue;
    std::mutex queue_access_mutex{};
    std::vector<std::thread> threads;
    std::vector<std::thread::id> threads_ids;
    std::mutex threads_access_mutex{};

    for (int i = 0; i < 14; i++) {
        clients.emplace_back();
        for (int j = 0; j < 10; j++)
            clients[i].push_back(i);
    }

    std::thread queue_push_thread(push_clients, &clients, &queue, &queue_access_mutex);

    sleep(2);
    while (!queue.empty()) {
        if (queue.size() >= 5) {
            auto *newvec = new std::vector<std::vector<int>*>;
            for (int i = 0; i < 5; i++) {
                std::unique_lock<std::mutex> newline_lock(queue_access_mutex);
                newvec->emplace_back(queue.front());
                queue.pop();
                newline_lock.unlock();
            }
            threads.emplace_back(std::thread{&one_queue, newvec, &threads_ids, &threads_access_mutex});
        } else if (threads_ids.empty()) {
            auto *newvec = new std::vector<std::vector<int>*>;
            for (int i = 0; i < queue.size(); i++) {
                std::unique_lock<std::mutex> newline_lock(queue_access_mutex);
                newvec->emplace_back(queue.front());
                queue.pop();
                newline_lock.unlock();
            }
            threads.emplace_back(std::thread{&one_queue, newvec, &threads_ids, &threads_access_mutex});
        }
        sleep(2);
    }

    std::cout << "Out" << std::endl;
    for (std::thread &thread : threads)
        thread.join();

    queue_push_thread.join();
    return EXIT_SUCCESS;
}