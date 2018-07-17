//The struct to solve the strongly connected components problem of a graph
//Strongly_Connected_Components(int n) - Build the struct with n vertex and no edge
//Strongly_Connected_Components(Graph G) - Build the struct base on the Graph G
//void ins(int x,int y) - Add an edge from x to y
//void tarjan() - Use tarjan algorithm to solve the strongly connected components
//void Kosaraju() - Use Kosaraju algorithm to solve the strongly connected components
//vector<VI> components() - Return every strongly connected components
//Graph rebuild() - Return the topological graph after tarjan algorithm
#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP
#define STRONGLY_CONNECTED_COMPONENTS_HPP
#include "Graph.hpp"
struct Strongly_Connected_Components:public Graph{
	static const int N=111111;
	int scc,id,bl[N];
	private:
		int t,dfn[N],low[N],q[N],mk[N];
		bool is[N];
		vector<VI>R;VI U;
		void tj(int x){
			int i,y,o=0;
			low[x]=dfn[x]=++id;is[x]=1;q[++t]=x;
			for(int y:TI.V[x])
				if(!dfn[y])tj(y),low[x]=min(low[x],low[y]);
				else if(is[y])low[x]=min(low[x],dfn[y]);
			if(dfn[x]==low[x]){
				VI W;
				for(scc++;o!=x;o=q[t--],bl[o]=scc,is[o]=0,W.PB(o));
				R.PB(W);
			}
		}
		void dfs1(int x){
			is[x]=1;U.PB(x);
			for(int y:TI.V[x])if(!is[y])dfs1(y);
		}
		void dfs2(int x,int num,const Graph &G){
			bl[x]=num;
			for(int y:G.V[x])if(!bl[y])dfs2(y,num,G);
		}
	public:
		Strongly_Connected_Components(int _n):Graph(_n){}
		Strongly_Connected_Components(Graph G){Graph::operator=(G);}
		void tarjan(){
			CL(dfn);CL(low);CL(is);scc=t=id=0;
			fr(i,n)if(!dfn[i])tj(i);
		}
		void Kosaraju(){//n^2/32 is on the way
			CL(is);CL(bl);U.clear();
			fr(i,n)if(!is[i])dfs1(i);
			Graph _G=Transpose_Graph(*this);
			for(int x:U)if(!bl[x])scc++,dfs2(x,scc,_G);
		}
		vector<VI> components(){return R;}
		Graph rebuild(){
			Graph G;CL(mk);
			fr(x,n)for(int y:TI.V[x])
				if(bl[x]!=bl[y]&&mk[bl[y]]!=x)mk[bl[y]]=x,G.ins(x,y);
			return G;
		}
};
#endif
