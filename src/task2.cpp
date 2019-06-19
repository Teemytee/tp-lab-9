#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

template <typename I, typename F>
void bubble_sort(I begin, I end, F &&functor) {
  std::mutex mutex;
  std::lock_guard<std::mutex> lock(mutex);
  bool is_swapped = true;
  auto end_iterator_copy = end;
  for (; begin != end-- && is_swapped;) {
    is_swapped = false;
    std::thread pool([&] (void) {
      for (auto index = begin; index != end_iterator_copy; ++index)
        std::cout << *index << " ";
      std::cout << "\n";
    });
    pool.join();
    for (auto iter = begin; iter != end; ++iter) {
      if (functor(*(iter + 1), *iter)) {
        std::iter_swap(iter, iter + 1);
        is_swapped = true;
      }
    }
  }
  return;
}

int main() {
  std::vector<int> a = {1, 3, 4, 2, 7, 6};
  bubble_sort(std::begin(a), std::end(a), [&](int a, int b) { return a < b; });
  return 0;
}
