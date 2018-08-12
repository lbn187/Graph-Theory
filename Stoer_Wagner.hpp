namespace Stoer_Wagner{
	using Val=LL;
	const int N=2222;
	const Val INF=1e18;
	Val e[N][N],s[N];int p[N];
	void clear(int n){fr(i,n)fr(j,n)e[i][j]=0;}
	void add(int x,int y,Val z){e[x][y]+=z;e[y][x]+=z;}
	Val SW(int n){
		Val ans=INF;
      fr(i,n)p[i]=i;
		for(;n>1;n--){
			fr(i,n)s[p[i]]=0;
			fr(i,n-1){
				int u=i+1;
				FR(j,i+1,n)if((s[p[j]]+=e[p[i]][p[j]])>s[p[u]])u=j;
				swap(p[i+1],p[u]);
			}
			Min(ans,s[p[n]]);
			fr(i,n-2)e[p[n-1]][p[i]]=e[p[i]][p[n-1]]+=e[p[i]][p[n]];
		}
		return ans;
	}
};
namespace Heap_Stoer_Wagner{
	using Val=LL;
	const int N=2222;
	const Val INF=1e18;
	vector<pair<int,Val>>e[N];
	Val s[N];DSU U;
	int p[N];bool v[N];
	void clear(int n){fr(i,n)e[i].clear();}
	void add(int x,int y,Val z){e[x].PB(MP(y,z));e[y].PB(MP(x,z));}
	Val SW(int n){
		Val ans=INF;
      fr(i,n)p[i]=i;
		for(U.init(n);n>1;n--){
			PQ<pair<Val,int>>h;
			fr(i,n)v[p[i]]=0,h.PH({s[p[i]]=0,p[i]});
			fr(i,n){
				int x,y;
				for(;h.top().X<s[x=h.top().Y];h.pop());
				v[p[i]=x]=1;h.pop();
				for(auto j:e[x])if(!v[y=U[j.X]]&&j.Y)h.PH({s[y]+=j.Y,y});
			}
			Min(ans,s[p[n]]);
			for(auto i:e[p[n]])e[p[n-1]].PB(i);
			e[p[n]]={};U[p[n]]=U[p[n-1]];
		}
		return ans;
	}
};
