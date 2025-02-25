#include <iostream>
#include <vector>
#include <algorithm>

void sortArrayWithTwoPointers(std::vector<int>& nums) {
   int n = nums.size();

    for (int i = 1; i < n; ++i) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = key;
    }
}

int main() {
    std::vector<int> nums = {2, 9, 1, 7, 3, 0, 4, 5, 8, 6};

    std::cout << "Original Array: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    sortArrayWithTwoPointers(nums);
    std::cout << "Sorted Array: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}