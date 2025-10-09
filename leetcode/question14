class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n=strs.size(),min=201,len=0;
        if(n==0)return "";
        bool check=true;
        for(int i=0;i<n;i++){
            if(strs[i][0]!=strs[0][0])return "";
            if(strs[i].length()<min)min=strs[i].length();
        }
        while(len<min&&check){
            for(int i=0;i<n;i++){
                if(strs[i][len]!=strs[0][len]){
                    return strs[0].substr(0,len);
                }
            }
            len++;
        }
        return strs[0].substr(0,len);
    }
};