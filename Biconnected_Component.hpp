//The struct to solve the biconnected components problem of a graph
#ifndef BICONNECTED_COMPONENT_HPP
#define BICONNECTED_COMPONENT_HPP
#include "Undirected_Graph.hpp"
struct Biconnected_Component:public Undirected_Graph{
	static const int N=111111;
	int id;
	VI GD;vector<PII>GB;
	private:
		int dfn[N],low[N];
		void dfs(int x,int fa){
			dfn[x]=low[x]=++id;
			int cd=0,o=0,ff=0;
			for(int y:TI.V[x])if(!dfn[y]){
				dfs(y,x);cd++;
				if(fa&&dfn[x]<=low[y]&&!ff)GD.PB(x),ff=1;
				if(low[y]>dfn[x])GB.PB(MP(min(x,y),max(x,y)));//if has multi edges, you should check it specially
				low[x]=min(low[x],low[y]);
			}else if(y!=fa)low[x]=min(low[x],dfn[y]);
			if(cd>1&&!fa&&!ff)GD.PB(x);
		}
	public:
		Biconnected_Component(int _n):Undirected_Graph(_n){}
		Biconnected_Component(Undirected_Graph G){Undirected_Graph::operator=(G);}
		void getcut(){
			id=0;CL(dfn);CL(low);
			fr(i,n)if(!dfn[i])dfs(i,0);
		}
		void printcutvertex(){
			sort(ALL(GD));
			for(int y:GD)printf("%d%c",y,y==GD.back()?'\n':' ');
		}
		void printcutedge(){
			sort(ALL(GB));
			for(PII o:GB)printf("%d %d\n",o.X,o.Y);
		}
		void clear(){
			Undirected_Graph::clear();
			CL(low);CL(dfn);
			GD.clear();GB.clear();
		}
};
#endif
