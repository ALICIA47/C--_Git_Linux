class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0; // 如果数组为空，返回 0

        int numk = 1; // 用于记录不重复元素的个数
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) { // 如果当前元素与前一个元素不同
                nums[numk] = nums[i]; // 将当前元素放到不重复元素的下一个位置
                numk++; // 增加不重复元素的个数
            }
        }
        return numk; // 返回不重复元素的个数
    }
};