#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T> std::ostream& operator<<(std::ostream& o, std::vector<T> const& vector) {
    for (auto const& v: vector) 
        o << v << " ";
    return o;
}

template <typename I, typename F>
void bubble_sort(I begin, I end, F&& functor) {
    bool is_swapped = true;
    for (; begin != end-- && is_swapped; ) {
        is_swapped = false;
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
    
    std::vector<int> a = {1, 3, 4, 2, 3, 1, 0, 4, 6};
    bubble_sort(std::begin(a), std::end(a), 
        [&](int l, int r) { return l < r; }
    );
    std::cout << a << "\n";
    bubble_sort(std::begin(a), std::end(a), 
        [&](int l, int r) { return l > r; });
    std::cout << a << "\n";
    bubble_sort(std::begin(a), std::end(a), 
        [&](int l, int r) { return l % r; });
    std::cout << a << "\n";

    return 0;
}