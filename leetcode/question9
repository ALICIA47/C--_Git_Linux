class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)
        {
            return false;
        }
        else if(x==0)
        {
            return true;
        }
        else if(x>0)
        {
            std::stringstream sx;
            sx<<x;
            std::string s=sx.str();
            int len=s.length();
            for(int i=0;i<len/2;i++)
            {
                if(s[i]!=s[len-i-1])
                {
                    return false;
                }
            }
           
        }
         return true;
    }
};
//3ms