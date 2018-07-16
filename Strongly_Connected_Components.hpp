//The struct to solve the strongly connected components problem of a graph
//Strongly_Connected_Components(int n) - Build the struct with n vertex and no edge
//Strongly_Connected_Components(Graph G) - Build the struct base on the Graph G
//void ins(int x,int y) - Add an edge from x to y
//void tarjan() - Use tarjan algorithm to solve the strongly connected components
//Graph rebuild() - Return the topological graph after tarjan algorithm
#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP
#define STRONGLY_CONNECTED_COMPONENTS_HPP
#include "Graph.hpp"
template<typename T> struct Strongly_Connected_Components:public Graph{
	static const int N=111111;
	static const T INF=1e9;
	int n,scc,id,bl[N];
	private:
		int t,dfn[N],low[N],q[N],mk[N];
		VI V[N];bool is[N];
		void tj(int x){
			int i,y,o=0;
			low[x]=dfn[x]=++id;is[x]=1;q[++t]=x;
			for(int y:V[x])
				if(!dfn[y])tj(y),low[x]=min(low[x],low[y]);
				else if(is[y])low[x]=min(low[x],dfn[y]);
			if(dfn[x]==low[x])for(scc++;o!=x;o=q[t--],bl[o]=scc,is[o]=0);
		}
	public:
		Strongly_Connected_Components(int _n):n(_n),Graph(_n){}
		Strongly_Connected_Components(Graph G):n(G.n){Graph::operator=(G);}
		void ins(int x,int y){Graph::ins(x,y);}
		void tarjan(){
			CL(dfn);CL(low);CL(is);scc=t=id=0;
			fr(i,n)if(!dfn[i])tj(i);
		}
		Graph rebuild(){
			Graph G;CL(mk);
			fr(x,n)for(int y:V[x])
				if(bl[x]!=bl[y]&&mk[bl[y]]!=x)mk[bl[y]]=x,G.ins(x,y);
			return G;
		}
};
#endif
