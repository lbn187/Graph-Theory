#ifndef DSU_HPP
#define DSU_HPP
#include"start.hpp"
struct DSU{
    static const int N=111111;
    int n,F[N];
    private:
    public:
        DSU()=default;
        DSU(int _n):n(_n){fr(i,n)F[i]=i;}
        DSU(const DSU&A):n(A.n){fr(i,n)F[i]=A.F[i];}
        DSU& operator=(const DSU&A){
            if(this==&A)return *this;
            n=A.n;
            fr(i,n)F[i]=A.F[i];
            return *this;
        }
        void init(int _n){n=_n;fr(i,n)F[i]=i;}
        int fd(int x){return F[x]==x?x:F[x]=fd(F[x]);}
        int& operator[](int x){return F[fd(x)];}
        void merge(int x,int y){F[fd(x)]=fd(y);}
};
#endif
