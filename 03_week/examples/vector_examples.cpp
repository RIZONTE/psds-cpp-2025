#include <iostream>
#include <vector>

void vector_init() {
    std::cout << __func__ << ':' << std::endl;
    std::vector<int> v1;                    // empty
    std::vector<int> v2(v1);            // copy ctor from other vector
    std::vector<int> v3 = v1;           // copy ctor from other vector
    // ctor
    std::vector<int> v4(5);             // 5 elemets with zero value
    std::vector<int> v5(5, 2);     // 5 elements equal 2
    // initializer list
    std::vector<int> v6{1, 2, 4, 5};       // with elements 1, 2, 4, 5
    std::vector<int> v7 = {1, 2, 3, 5};    // with elements 1, 2, 3, 5
    // iterators
    std::vector<int> v8(v7.begin(), v7.end()); // same as v7
    std::cout << std::endl;
}

void vector_reallocation() {
    std::cout << __func__ << ':' << std::endl;
    std::vector<int> v;
    size_t capacity = v.capacity();

    std::cout << v.data() << std::endl; // int* (address)
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
        if (capacity < v.capacity()) {
            capacity = v.capacity();

            std::cout << v.data() << std::endl; // int* (address)
            std::cout << v.size() << ' ' << v.capacity() << std::endl;
        }
    }
    std::cout << std::endl;
}

void vector_iterating() {
    std::cout << __func__ << ':' << std::endl;

    std::vector<int> v = {1, 2, 3, 5};
    std::cout << "range_based for:" << std::endl;
    for (auto vi : v) {
        std::cout << vi << " ";
    }
    std::cout << std::endl;

    std::cout << "using [idx]:" << std::endl;
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "forward iterating:" << std::endl;
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "reverse iterating:" << std::endl;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

void vector_reserve() {
    std::cout << __func__ << ':' << std::endl;
    std::vector<int> v;
    v.reserve(100);
    for (size_t i = 0; i < 100; ++i) {
       v.push_back(i);
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

int main() {
    vector_init();
    vector_reallocation();
    vector_iterating();
    vector_reserve();
}


