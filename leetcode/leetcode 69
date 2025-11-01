class Solution {
public:
    int mySqrt(int x) {
        if(x==0)
        {
            return 0;
        }
        else if(x==1)
        {
            return 1;
        }
        else
        {
            int l=1,r=x,res=0;
            while(l<=r)
            {
                int mid=l+(r-l)/2;
                if(mid<=x/mid)
                {
                    res=mid;
                    l=mid+1;
                }
                else
                {
                    r=mid-1;
                }
            }
            return res;
        }
        
    }
};