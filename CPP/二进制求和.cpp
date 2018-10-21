class Solution {
public:
    string addBinary(string a, string b) {
        int plus=0;
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
        int len=max(a.size(),b.size());
        string c(len,'0');
        for(int i=0;i<len;i++){
            if(a.size()<len)a+='0';
            if(b.size()<len)b+='0';
        }
        for(int i=0;i<len;i++){
            if(a[i]=='1'&&b[i]=='1'){
                if(plus)c[i]='1';
                else c[i]='0';
                plus=1;
            }
            if((a[i]=='0'&&b[i]=='1')||(a[i]=='1'&&b[i]=='0')){
                if(plus){
                    c[i]='0';
                    plus=1;
                }
                else
                    c[i]='1';
            }
            if(a[i]=='0'&&b[i]=='0'){
                if(plus)c[i]='1';
                else c[i]='0';
                plus=0;
            }
        }
        if(plus)
            c+='1';
        reverse(c.begin(),c.end());
        return c;
        
    }
};