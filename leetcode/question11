class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxSize = 0;
        int n = height.size();
        int l = 0, r = n - 1;

        while (l < r) {
            int minHeight = min(height[l], height[r]);
            int currentSize = minHeight * (r - l);
            maxSize = max(maxSize, currentSize);

            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }
        return maxSize;
    }
};//8ms