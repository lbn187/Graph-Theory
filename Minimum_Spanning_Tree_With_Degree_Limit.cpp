const int INF=1e9;
LL ans;
int n,m,S,K,cnt,Best[N],fa[N],FE[N];
int o,f[N],p[M],t[M],c[M],Cost[N];
bool u[M],d[M];PII MinCost[N];
struct Edge{
	int x,y,z;
	bool operator<(const Edge&E)const{return z<E.z;}
}E[M];
VI V;
int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
void add(int x,int y,int z){p[++o]=y;c[o]=z;t[o]=f[x];f[x]=o;}
void dfs(int x,int F){
	fa[x]=F;
	if(F==S)Best[x]=-1;else{
		Best[x]=x;
		if(~Best[F]&&Cost[Best[F]]>Cost[x])Best[x]=Best[F];
	}
	for(int y=f[x];y;y=t[y])
		if(!d[y]&&p[y]!=F){
			Cost[p[y]]=c[y];
			FE[p[y]]=y;
			dfs(p[y],x);
		}
}
bool Kruskal(){
	cnt=n-1;ans=0;o=1;
	fr(i,n)fa[i]=i,f[i]=0;
	sort(E+1,E+m+1);
	fr(i,m){
		if(E[i].y==S)swap(E[i].x,E[i].y);
		if(E[i].x!=S&&gf(E[i].x)!=gf(E[i].y)){
			fa[gf(E[i].x)]=gf(E[i].y);
			ans+=E[i].z;
			cnt--;
			u[i]=1;
			add(E[i].x,E[i].y,E[i].z);
			add(E[i].y,E[i].x,E[i].z);
		}
	}
	fr(i,n)MinCost[i]=MP(INF,INF);
	fr(i,m)if(E[i].x==S){
		V.PB(i);
		MinCost[gf(E[i].y)]=min(MinCost[gf(E[i].y)],MP(E[i].z,i));
	}
	int dif=0;
	fr(i,n)if(i!=S&&fa[i]==i){
		if(MinCost[i].Y==INF)return 0;
		if(++dif>K)return 0;
		dfs(E[MinCost[i].Y].y,S);
		u[MinCost[i].Y]=1;
		ans+=MinCost[i].X;
	}
	return 1;
}
bool Solve(){//If it's ok, ans store the answer
	CL(d);CL(u);VI W;
	fr(i,m)if(E[i].x==S||E[i].y==S)W.PB(E[i].x+E[i].y-S);
	sort(W.begin(),W.end());
	W.erase(unique(W.begin(),W.end()),W.end());
	if(W.size()<K)return 0;
	if(!Kruskal())return 0;
	for(int i=cnt+1;i<=K&&i<=n;i++){
		int MinD=INF,MinID=-1;
		for(int j=V.size()-1;j>=0;j--)if(u[V[j]])V.erase(V.begin()+j);
		for(auto y:V){
			int tmp=E[y].z-Cost[Best[E[y].y]];
			if(tmp<MinD)MinD=tmp,MinID=y;
		}
		if(MinID==-1)return 1;
		if(MinD>=0)break;
		ans+=MinD;
		u[MinID]=1;
		d[FE[Best[E[MinID].y]]]=d[FE[Best[E[MinID].y]]^1]=1;
		dfs(E[MinID].y,S);
	}
	return 1;
}
