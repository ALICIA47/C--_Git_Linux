class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int last=digits.size();
        int Position=0;
        if(digits[0]==0)
        {
            digits[0]=1;
            return digits;
        }
        else
        {
            if(digits[last-1]!=9)
            {
                digits[last-1]+=1;
            }
            else
            {
                bool whether99 =true;
                for(int i=last-1;i>=0;i--)
                {
                    if(digits[i]!=9)
                    {
                        Position=i;
                        whether99=false;
                        break;
                    }
                }
                if(whether99)
                {
                    digits.resize(last+1);
                    digits[0]=1;
                    for(int j=1;j<=last;j++)
                    {
                        digits[j]=0;
                    }
                }
                else
                {
                    digits[Position]+=1;
                    for(int j=Position+1;j<last;j++)
                    {
                        digits[j]=0;
                    }
                }
            }
        }
        return digits;
    }
};