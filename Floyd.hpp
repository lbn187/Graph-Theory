template<typename T,const int N,const T INF>Floyd{
    int n;
    T d[N][N];
    Floyd()=default;
    Floyd(int _n):{init(_n);}
    Floyd(int _n,T** _d):n(_n){
        fr(i,n)fr(j,n)d[i][j]=_d[i][j];
    }
    void clear(){
        fr(i,n)fr(j,n)d[i][j]=INF;
        fr(i,n)d[i][i]=0;
    }
    void init(int _n){
        n=_n;
        clear();
    }
    void ins(int x,int y,T z){d[x][y]=min(d[x][y],z);}
    void work(){
        fr(k,n)fr(i,n)if(i!=k)
		    fr(j,n)if(i!=j&&k!=j)
		        if(d[i][k]+d[k][j]<d[i][j])d[i][j]=d[i][k]+d[k][j];
    }
}
