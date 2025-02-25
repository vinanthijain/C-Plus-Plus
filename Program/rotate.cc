#include <vector>
#include <algorithm>  // For std::rotate and std::swap
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    std::rotate(vec.begin() + 2, vec.begin() + 3, vec.end());
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    std::swap(vec[0], vec[4]);
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

