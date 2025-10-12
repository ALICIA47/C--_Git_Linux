class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        unordered_map<char, string> phoneMap = {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
        };
        vector<string> result;
        string currentCombination;
        backtrack(digits, phoneMap, 0, currentCombination, result);
        return result;
    }
private:
    void backtrack(const string& digits, const unordered_map<char, string>& phoneMap, int index, string& currentCombination, vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(currentCombination);
            return;
        }
        char digit = digits[index];
        const string& letters = phoneMap.at(digit);
        for (char letter : letters) {
            currentCombination.push_back(letter);
            backtrack(digits, phoneMap, index + 1, currentCombination, result);
            currentCombination.pop_back();
        }
    }
};