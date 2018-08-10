namespace Minimum_Spanning_Tree_With_Degree_Limit{
    const int N=111111;
    const int M=1111111;
    const int INF=1e9;
    LL ans;
    int n,m,S,K,cnt,Best[N],fa[N],FE[N];
    int o,f[N],p[M],t[M],c[M],Co[N];
    bool u[M],d[M];
    PII MiCo[N];//first记录值，second记录边
    VI V;
    struct Edge{
	    int x,y,z;
	    bool operator<(const Edge&E)const{return z<E.z;}
    }E[M];
    int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
    void add(int x,int y,int z){p[++o]=y;c[o]=z;t[o]=f[x];f[x]=o;}
    void dfs(int x,int F){//DP
	    fa[x]=F;
	    if(F==S)Best[x]=-1;else{
		    Best[x]=x;
		    if(~Best[F]&&Co[Best[F]]>Co[x])Best[x]=Best[F];
	    }
	    for(int y=f[x];y;y=t[y])
		    if(!d[y]&&p[y]!=F)Co[p[y]]=c[y],FE[p[y]]=y,dfs(p[y],x);
    }
    bool Kruskal(){//先将S剔除做Kruskal，弄成若干联通块 
	    cnt=n-1;ans=0;o=1;
	    fr(i,n)fa[i]=i,f[i]=0;
	    sort(E+1,E+m+1);
	    fr(i,m){
		    if(E[i].y==S)swap(E[i].x,E[i].y);
		    if(E[i].x!=S&&gf(E[i].x)!=gf(E[i].y)){
			    fa[gf(E[i].x)]=gf(E[i].y);
			    ans+=E[i].z;cnt--;
			    add(E[i].x,E[i].y,E[i].z);add(E[i].y,E[i].x,E[i].z);
		    }
	    }
	    fr(i,n)MiCo[i]=MP(INF,INF);
	    fr(i,m)if(E[i].x==S)V.PB(i),MiCo[gf(E[i].y)]=min(MiCo[gf(E[i].y)],MP(E[i].z,i));
	    int dif=0;
	    fr(i,n)if(i!=S&&fa[i]==i){
		    if(MiCo[i].Y==INF)return 0;
		    if(++dif>K)return 0;
		    dfs(E[MiCo[i].Y].y,S);
		    u[E[MiCo[i].Y].y]=1;
		    ans+=MiCo[i].X;
	    }
	    return 1;
    }
    LL Solve(int _n,int _m,int _S,int _K,vector<tuple<int,int,int>>edge){//如果无解，返回-1
        n=_n;S=_S;K=_K;
        for(auto o:edge)E[++m]=Edge{get<0>(o),get<1>(o),get<2>(o)};
        CL(d);CL(u);VI W;
	    fr(i,m)if(E[i].x==S||E[i].y==S)W.PB(E[i].x+E[i].y-S);
	    sort(W.begin(),W.end());
	    W.erase(unique(W.begin(),W.end()),W.end());
	    if(W.size()<K)return -1;//注意特判度数不超过K的情况 
	    if(!Kruskal())return -1;
	    for(int i=cnt+1;i<=K&&i<=n;i++){
	    	int MinD=INF,MinID=-1,tmp;
		    for(int j=V.size()-1;j>=0;j--)if(u[E[V[j]].y])V.erase(V.begin()+j);
		    for(auto y:V)if(tmp=E[y].z-Co[Best[E[y].y]],tmp<MinD)MinD=tmp,MinID=E[y].y;
		    if(MinID==-1)return ans;
		    //如果MinD<0，而且题目要求度数不超过K即可，应该加brek
		    ans+=MinD;u[MinID]=1;
		    d[FE[Best[MinID]]]=d[FE[Best[MinID]]^1]=1;
		    dfs(MinID,S);
	    }
	    return ans;
    }
};
