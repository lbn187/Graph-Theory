#include "Undirected_Graph.hpp"
struct Maximum_Matching{
	static const int N=1111;
	Undirected_Graph G;
	int n,m,mat[N];
	private:
		int W,h,t,F[N],pre[N],tp[N],q[N],vs[N];
		int fd(int x){return F[x]?F[x]=fd(F[x]):x;}
		int lca(int u,int v){
			for(++W;;u=pre[mat[u]],swap(u,v))
				if(vs[u=fd(u)]==W)return u;else vs[u]=u?W:0;
		}
		void aug(int u,int v){
			for(int w;u;v=pre[u=w])w=mat[v],mat[mat[u]=v]=u;
		}
		void blo(int u,int v,int f){
			for(int w;fd(u)^f;u=pre[v=w])
				pre[u]=v,F[u]?0:F[u]=f,F[w=mat[u]]?0:F[w]=f,tp[w]^1?0:tp[q[++t]=w]=-1;
		}
		int bfs(int u){
			int x,i;
			fr(i,n)tp[i]=F[i]=0;
			for(--tp[q[h=t=1]=u];h<=t;u=q[++h])
				for(int y:G.V[u])if(!tp[y]){
					if(!mat[y])return aug(y,u),1;
					pre[y]=u,++tp[y],--tp[q[++t]=mat[y]];
				}else if(tp[y]^1&&fd(u)^fd(y))blo(u,y,x=lca(u,y)),blo(y,u,x);
			return 0;
		}
	public:
		Maximum_Matching():n(0),m(0){}
		Maximum_Matching(Undirected_Graph _G):n(_G.n),m(_G.m){G=_G;}
		void ins(int x,int y){G.ins(x,y);m++;}
		int solve(){
			int i,an=0;W=0;
			fr(i,n)mat[i]?0:an+=bfs(i);
			return an;
		}
		void print(){
			fr(i,n)printf("%d%c",mat[i],i==n?'\n':' ');	
		}
}G;
