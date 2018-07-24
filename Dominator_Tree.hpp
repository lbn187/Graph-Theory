//The struct to solve dominator tree problem
//Dominator_Tree(n,s) - Build the struct with n vertex and start from vertex s
//Dominator_Tree(G,s) - Build the struct based on Graph G and start from vertex s
//work() - Work the Dominator Tree algorithm
//buildtree() - Build the Dominator Tree
//printtree() - Print the Dominator Tree
#ifndef DOMINATOR_TREE_HPP
#define DOMINATOR_TREE_HPP
#include "Graph.hpp"
#include "Tree.hpp"
struct Dominator_Tree:Graph{
	static const int N=444444;
	int s,dfn[N],id[N],idom[N];
	private:
		int cnt,pa[N],semi[N],p[N],mn[N];
		VI dom[N],be[N];
		void dfs(int x){
			dfn[x]=++cnt;id[cnt]=x;
			for(int y:V[x]){
				if(!dfn[y])dfs(y),pa[dfn[y]]=dfn[x];
				be[dfn[y]].PB(dfn[x]);
			}
		}
		int get(int x){
			if(p[x]!=p[p[x]]){
				if(semi[mn[x]]>semi[get(p[x])])mn[x]=get(p[x]);
				p[x]=p[p[x]];
			}
			return mn[x];
		}
		void LT(){
			for(int i=cnt;i>1;i--){
				for(int j:be[i])semi[i]=min(semi[i],semi[get(j)]);
				dom[semi[i]].PB(i);
				int x=p[i]=pa[i];
				for(int y:dom[x])idom[y]=(semi[get(y)]<x?get(y):x);
				dom[x].clear();
			}
			for(int i=2;i<=cnt;i++){
				if(idom[i]!=semi[i])idom[i]=idom[idom[i]];
				dom[id[idom[i]]].PB(id[i]);
			}
		}
	public:
		Dominator_Tree()=default;
		Dominator_Tree(int _n,int _s):Graph(_n),s(_s){}
		Dominator_Tree(Graph G,int _s):s(_s),Graph(G){}
		void work(){
			fr(i,n)dfn[i]=0,dom[i].clear(),be[i].clear(),p[i]=mn[i]=semi[i]=i;
			cnt=0;dfs(s);LT();
		}
		Tree buildtree(){
			Tree W(n);
			fr(i,n)if(id[idom[i]])W.ins(id[idom[i]],id[i]);
			return W;
		}
		void printtree(){
			fr(i,n)if(id[idom[i]])printf("%d --> %d\n",id[idom[i]],id[i]);
		}
};
#endif
