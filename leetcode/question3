class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLength = 0;
        unordered_map<char, int> charIndexMap;
        int left = 0;

        for (int right = 0; right < n; right++) {
            if (charIndexMap.find(s[right]) != charIndexMap.end()) {
                left = max(charIndexMap[s[right]] + 1, left);
            }
            charIndexMap[s[right]] = right;
            maxLength = max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};//11ms