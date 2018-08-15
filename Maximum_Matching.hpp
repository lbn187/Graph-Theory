//function - Using blossom tree to solve the maximum matching problem
//n - The number of vertexs
//m - The number of edges
//mat[i] - The matching vertex of the vertex i
//Maximum_Matching(n) - Make a Maximum_Matching struct has n vertexs
//Maximum_Matching(G) - Make a Maximum_Matching struct based on G
//solve() - Using blossom turee to solve the maximum matching problem, which time complixity is O(n^3)
//print() - Print the scheme
#ifndef MAXIMUM_MATCHING_HPP
#define MAXIMUM_MATCHING_HPP
#include "Undirected_Graph.hpp"
struct Maximum_Matching:public Undirected_Graph{
	int mat[N];
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
			int x,E,i;
			fr(i,n)tp[i]=F[i]=0;
			for(h=0,--tp[q[t=1]=u];h^t;)
			for(int E:V[u=q[++h]])if(!tp[E]){
				if(!mat[E])return aug(E,u),1;
				pre[E]=u,++tp[E],--tp[q[++t]=mat[E]];
			}else if (tp[E]^1&&fd(u)^fd(E))blo(u,E,x=lca(u,E)),blo(E,u,x);
			return 0;
		}
	public:
		Maximum_Matching()=default;
		Maximum_Matching(Undirected_Graph _G):Undirected_Graph(_G){}
		int solve(){
			int i,an=0;W=0;
			fr(i,n)pre[i]=vs[i]=mat[i]=0; 
			fr(i,n)mat[i]?0:an+=bfs(i);
			return an;
		}
		void print(){fr(i,n)printf("%d%c",mat[i],i==n?'\n':' ');}
};
#endif
