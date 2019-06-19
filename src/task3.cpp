#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <random>
#include <queue>
#include <atomic>

using namespace std::chrono_literals;

namespace rnd {
  template <typename T> auto get_random(T lower_bound, T upper_bound) {
    static std::mt19937_64 mersenne_twister {std::random_device{}()};
    std::uniform_int_distribution distribution (lower_bound, upper_bound);
    return distribution (mersenne_twister);
  }
}

namespace {
  std::mutex mutex;
  static std::size_t queue_id;
}

template <typename C> auto clear_container(C& container) {
  C empty_container;
  std::swap(container, empty_container);
}

auto get_thread_identificator() noexcept {
  static std::atomic<std::size_t> thread_id {0};
  thread_local std::size_t id = thread_id;
  ++thread_id;
  return id;
}

auto serve_simulation(std::queue<std::vector<std::size_t>> customers) {
  std::lock_guard<std::mutex> lock_guard (mutex);
  for (; !customers.empty(); ) {
    for (std::size_t index = 0; index < customers.front().size(); ++index) {
      std::cout << "OK. Got " << index << " " << get_thread_identificator() << " " << "\n";
      std::this_thread::sleep_for(0.04s);
    }
    customers.pop();
  }
}

int main() {
  std::queue<std::vector<std::size_t>> customers;
  std::vector<std::thread*> threads;
  auto queue_size = rnd::get_random(100, 1000);
  for (std::size_t index = 0; index < queue_size; ++index) {
    auto products_amount = rnd::get_random(2, 10);
    std::vector<std::size_t> products (products_amount);
    for (std::size_t j = 0; j < products_amount; ++j) {
      products[j] = rnd::get_random(50, 1000);
    }
    customers.push(products);
    std::cout << "Queues: " << customers.size() << "\n";
    if (customers.size() % 5 == 0 && customers.size() != 0) {
      threads.push_back(new std::thread(serve_simulation, customers));
      std::cout << "Threads: " << threads.size() << "\n";
      clear_container(customers);
    }
  }

  for (auto const& thread: threads) thread->join();

  return 0;
}
