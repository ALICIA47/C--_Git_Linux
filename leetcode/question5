class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty())return "";
        int start=0,end=0;
        for(int i=0;i<s.length();i++){
            int length1=kuozhan(s,i,i);
            int length2=kuozhan(s,i,i+1);
            int len=max(length1,length2);
            if(len>end-start){
                start=i-(len-1)/2;
                end=i+len/2;
            }
        }
        return s.substr(start,end-start+1);
    }
private:
    int kuozhan(const string &s,int left,int right){
        while(left>=0&&right<s.length()&&s[left]==s[right]){
            left--;
            right++;
        }
        return right-left-1;
    }
};