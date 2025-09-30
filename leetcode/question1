class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map; // 创建一个哈希表
        vector<int> res(2); // 用于存储结果的向量

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i]; // 计算目标值与当前值的差
            if (num_map.find(complement) != num_map.end()) { // 检查差值是否在哈希表中
                res[0] = num_map[complement]; // 如果在，存储差值的索引
                res[1] = i; // 存储当前值的索引
                return res; // 返回结果
            }
            num_map[nums[i]] = i; // 将当前值和索引存储到哈希表中
        }

        return res; // 返回结果
    }
};//0ms