//function: a struct to solve bipartitle graph problem
//ln - The number of vertex in the left part
//rn - The number of vertex in the right part
//m - The number of edges
//lkx[i] - The vertex match the left part vertex i
//lky[i] - The vertex match the right part vertex i
//Bipartite_Graph(n,m) - Make a Bipartite_Graph struct with n vertexs in the left part and m vertexs in the right part
//Bipartite_Graph(G,n,m) - Make a Bipartite_Graph struct with n vertexs in the left part and m vertexs in the right part and based on Graph G
//ins(x,y) - Add an edge from left part vertex x to right part vertex y
//Hungary(n) - Use Hungary algorithm to solve the maximum match of Bipartite_Graph, which time complexity is O(nm)
//Hopcroft_Kart(n) - Use Hopcroft Kart algorithm to solve the maximum match of Bipartite_Graph, which time complexity is O(mn^(0.5)) 
//print() - Print the maximum match scheme
//pair<VI,VI> Minimum_Vertex_Coverage() - Return the minimum vertex coverage of the Bipartite_Graph
//pair<VI,VI> Largest_Independent_Set() - Return the Largest independent set of the Bipartite_Graph
//pair<VI,VI> Maximum_Clique() - Return the maximum clique of the Bipartite_Graph
//int Minimum_Path_Coverage(G) -Return the minimum path coverage of the graph G
#ifndef BIPARTITE_GRAPH_HPP
#define BIPARTITE_GRAPH_HPP
#include "Graph.hpp"
struct Bipartite_Graph{
	static const int N=1111;
	Graph G;int ln,rn,m,lky[N],lkx[N];
	private:
		int v[N],dx[N],dy[N];bool vl[N],vr[N];
		void start(){
			fr(i,rn)lky[i]=v[i]=0;
			fr(i,ln)lkx[i]=0;
		}
		bool Hungary_Find(int x,int z){
			for(int y:G.V[x])if(v[y]!=z)
				if(v[y]=z,!lky[y]||Hungary_Find(lky[y],z))
					return lky[y]=x,lkx[x]=y,1;
			return 0;
		}
		bool HKbfs(){
			fr(i,ln)dx[i]=0;fr(i,m)dy[i]=0;
			queue<int>Q;int dis=ln+rn+1;
			fr(i,ln)if(!lkx[i])Q.push(i);
			for(;!Q.empty();){
				int x=Q.front();Q.pop();
				if(dx[x]>dis)continue;
				for(int y:G.V[x])if(!dy[y])
					if(dy[y]=dx[x]+1,lky[y])dx[lky[y]]=dy[y]+1,Q.push(lky[y]);
					else dis=dy[y];
			}
			return dis<=ln+rn;
		}
		bool HKdfs(int x,int z){
			for(int y:G.V[x])if(v[y]!=z&&dy[y]==dx[x]+1)
				if(v[y]=z,!lky[y]||HKdfs(lky[y],z))
					return lkx[x]=y,lky[y]=x,1;
			return 0;
		}
		void Scheme_dfs(int x){
			vl[x]=1;
			for(int y:G.V[x])if(!vr[y]&&lky[y])vr[y]=1,Scheme_dfs(lky[y]);
		}
		void Scheme_Find(){
			fr(i,ln)vl[i]=0;fr(i,rn)vr[i]=0;
			fr(i,ln)if(!lkx[i])Scheme_dfs(i);
		}
	public:
		Bipartite_Graph(int _ln,int _rn):ln(_ln),rn(_rn),m(0){}
		Bipartite_Graph(Graph _G,int _ln,int _rn):ln(_ln),rn(_rn){G=_G;m=G.m;}
		void ins(int x,int y){G.ins(x,y);m++;}
		int Hungary(){
			int an=0;
			start();
			fr(i,ln)if(Hungary_Find(i,i))an++;
			return an;
		}
		int Hopcroft_Karp(){
			int an=0,TM=0;
			fr(i,ln)lkx[i]=0;fr(i,rn)lky[i]=0;
			for(;an<min(ln,rn)&&HKbfs();)
				fr(i,ln)if(!lkx[i]&&HKdfs(i,++TM))an++;
			return an;
		}
		void print(){
			fr(i,rn)if(lky[i])printf("%d - %d\n",lky[i],i);
		}
		pair<VI,VI> Minimum_Vertex_Coverage(){
			Scheme_Find();
			VI VL,VR;
			fr(i,ln)if(lkx[i]&&!vl[i])VL.PB(i);
			fr(i,rn)if(vr[i])VR.PB(i);
			return MP(VL,VR);
		}
		pair<VI,VI> Largest_Independent_Set(){
			Scheme_Find();
			VI VL,VR;
			fr(i,ln)if(!lkx[i]||vl[i])VL.PB(i);
			fr(i,rn)if(!vr[i])VR.PB(i);
			return MP(VL,VR);
		}
		pair<VI,VI> Maximum_Clique(){
			Bipartite_Graph W(Anti_Graph(G),ln,rn);
			return W.Largest_Independent_Set();
		}
		pair<VI,VI> Essential_Vertex(){//have not finished yet
		}
};
int Minimum_Path_Coverage(Graph _G){
	Bipartite_Graph G(_G.n,_G.n);
	fr(x,_G.n)for(int y:_G.V[x])G.ins(x,y);
	return _G.n-G.Hungary();
}
#endif
