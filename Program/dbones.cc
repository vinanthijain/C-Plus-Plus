#include <iostream>
#include <vector>

using namespace std;

bool solve(std::vector<int>& nums) {
int preVal = nums[0];
bool consqOnes = false;
for(int i = 1; i < nums.size(); i++) {
if (preVal == 1 && nums[i] == 1) {
consqOnes = true;
} else if (preVal != 1 && nums[i] == 1) {
if (consqOnes == false) {
consqOnes = true;
} else {
return false;
}
}
preVal = nums[i];
}
return true;
}

int main() {
vector<int> array = {0,1,1,1,2,3};
cout << solve(array) << endl;

vector<int> array2 = {1,1,0,0,1,1};
cout << solve(array2) << endl;
}
