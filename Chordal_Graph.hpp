#ifndef CHORDAL_GRAPH_HPP
#define CHORDAL_GRAPH_HPP
#include "Graph.hpp"
#include "Tree.hpp"
struct Chordal_Graph:public Graph{
	static const int N=111111;
	int n,id[N],seq[N];
	private:
		int label[N],vis[N],c[N];
		bool gg[N];
	public:
		Chordal_Graph()=default;
		Chordal_Graph(int _n):Graph(_n){}
		Chordal_Graph(Graph G):Graph(G){}
		void mcs(){
			CL(id);CL(label);CL(seq);
			PQ<PII>Q;int x;
			fr(i,n)Q.push(MP(0,i));
			dr(i,n){
				for(;id[Q.top().Y];Q.pop());
				x=Q.top().Y;Q.pop();id[x]=i;
				for(int y:V[x])if(!id[y])
					label[y]++,Q.push(MP(-label[y],y));
			}
			fr(i,n)seq[id[i]]=i;
		}
		bool Chordal_Graph_Judge(){
			int x,w;CL(vis);
			fr(i,n){
				x=seq[i];VI Q;
				for(int y:V[x])
					if(id[y]>id[x])Q.PB(y);
				if(!SZ(Q))continue;
				w=Q[0];
				for(int y:Q)if(id[y]<id[w])w=y;
				for(int y:V[w])vis[y]=i;
				for(int y:Q)if(y!=w)if(vis[y]!=i)return 0;
			}
			return 1;
		}
		pair<int,int*> Minimum_Coloring(){
			CL(vis);CL(c);
			int an=0,x,j;
			dr(i,n){
				x=seq[i];
				for(int y:V[x])vis[c[y]]=i;
				for(j=1;vis[j]==i;j++);
				c[x]=j;
				an=max(an,j);
			}
			return MP(an,c);
		}
		VI Maximum_Independent_Set(){
			int x,ff;VI W;CL(gg);
			fr(i,n){
				x=seq[i];ff=0;
				for(int y:V[x])if(gg[y])ff=1;
				if(!ff)W.PB(i),gg[x]=1;
			}
		}
		VI Mining_Maximal_Cliques(int x){
		}
		VI Mining_Maximal_Cliques_Judge(VI W){
		}
		vector<VI> Minimum_Clique_Cover(){
		}
		Tree Chordal_Graph_Tree(){
		}
};
#endif 
