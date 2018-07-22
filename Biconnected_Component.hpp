//The struct to solve the biconnected components problem of a graph
//Biconnected_Component(n) - Build the biconnected components with n vertex and no edge
//Biconnected_Component(G) - Build the biconnected components based on the undirected graph G
//void clear() - Clear the biconnected components struct
//void getcut() - Get the cut vertex and the cut edge of the graph
//void printcutvertex() - Print the cur vertex of the graph
//void printcutedge() - Print the cut edge of the graph
//VI cutvertex() - Get the cut vertex of the graph
//vector<PII> cutedge() - Get the cut edge of the graph
//pair<vector<PII>,int > rebuild() - Return the topological tree edges and the number of vertex after the tarjan algorithm
#ifndef BICONNECTED_COMPONENT_HPP
#define BICONNECTED_COMPONENT_HPP
#include "Undirected_Graph.hpp"
struct Biconnected_Component:public Undirected_Graph{
	static const int N=111111;
	int id;
	VI GD;vector<PII>GB;
	private:
		int dfn[N],low[N];
		int t,scc,q[N],bl[N];vector<PII>W;
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
		void tj(int x,int fa){
			dfn[x]=low[x]=++id;q[++t]=x;int o=0;
			for(int y:V[x])if(!dfn[y]){
				tj(y,x);low[x]=min(low[x],low[y]);
				if(low[y]>=dfn[x])for(W.PB(MP(x,++scc));y!=-o;W.PB(MP(scc,o)))bl[o=q[t--]]=scc;
			}else if(y!=fa)low[x]=min(low[x],dfn[y]);
		}
	public:
		Biconnected_Component(int _n):Undirected_Graph(_n){}
		Biconnected_Component(Undirected_Graph G){Undirected_Graph::operator=(G);}
		void clear(){
			Undirected_Graph::clear();
			CL(low);CL(dfn);
			GD.clear();GB.clear();
		}
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
		VI cutvertex(){
			sort(ALL(GD));
			return GD;
		}
		vector<PII> cutedge(){
			sort(ALL(GB));
			return GB;
		}
		pair<int,vector<PII> > rebuild(){
			t=id=0;scc=n;CL(dfn);CL(low);W.clear();
			fr(i,n)if(!dfn[i])tj(i,0);	
			return MP(scc,W);
		}
};
#endif
