#include <iostream>
#include <vector>

int maxSumSubarray(const std::vector<int>& nums, int k) {
    int n = nums.size();
    int currentSum = 0;

    // Calculate the sum of the first window of size k
    for (int i = 0; i < k; ++i) {
        currentSum += nums[i];
    }

    int maxSum = currentSum;

    // Slide the window through the array
    for (int i = k; i < n; ++i) {
        // Subtract the element going out of the window
        currentSum -= nums[i - k];
        // Add the new element coming into the window
        currentSum += nums[i];
        // Update the maximum sum
        maxSum = std::max(maxSum, currentSum);
    }

    return maxSum;
}

int main() {
    // Example usage:
    std::vector<int> nums = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    int k = 3;

    int result = maxSumSubarray(nums, k);

    std::cout << "Maximum Sum of Subarray of Size " << result <<endl;
}