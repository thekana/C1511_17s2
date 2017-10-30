//Greatest common divisor
//King z5176970, Quinn z5142018
//2018-10-28 Zain F09A

int gcdRec(int a,int b) {
    int q=0;
    if(b==0) {
        q=a;
    } else {
        q=gcdRec(b,a%b);
    }
    return q;
}
