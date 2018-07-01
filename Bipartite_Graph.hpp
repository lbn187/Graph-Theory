//n - The number of vertex in the left part
//m - The number of vertex in the right part
//k - The number of edges
//lk[i] - The vertex match the right part vertex i
//lkx[i] - The vertex match the left part vertex i
//Bipartite_Graph(n,m) - Make a Bipartite_Graph struct with n vertexs in the left part and m vertexs in the right part
//Bipartite_Graph(G,n,m) - Make a Bipartite_Graph struct with n vertexs in the left part and m vertexs in the right part and based on Graph G
//ins(x,y) - Add an edge from left part vertex x to right part vertex y
//Hungary(n) - Use Hungary algorithm to solve the maximum match of Bipartite_Graph, which time complexity is O(nm)
//print() - Print the maximum match scheme
//pair<VI,VI> Minimum_Vertex_Coverage() - Return the minimum vertex coverage of the Bipartite_Graph
//pair<VI,VI> Largest_Independent_Set() - Return the Largest independent set of the Bipartite_Graph
//pair<VI,VI> Maximum_Clique() - Return the maximum clique of the Bipartite_Graph
#include "Graph.hpp"
struct Bipartite_Graph{
	Graph G;int n,m,k,lky[N],lkx[N];
	private:
		int v[N];bool vl[N],vr[N];
		void start(){
			fr(i,m)lky[i]=v[i]=0;
			fr(i,n)lkx[i]=0;
		}
		bool fd(int x,int z){
			for(int y:G.V[x])if(v[y]!=z)
				if(v[y]=z,!lky[y]||fd(lky[y],z))return lky[y]=x,1;
			return 0;
		}
		void get(int x){
			vl[x]=1;
			for(int y:G.V[x])if(!vr[y]&&lky[y])vr[y]=1,get(lky[y]);
		}
		void find(){
			fr(i,n)vl[i]=0;fr(i,m)vr[i]=0;
			fr(i,n)if(!lkx[i])get(i);
		}
	public:
		Bipartite_Graph(int _n,int _m){n=_n;m=_m;k=0;}
		Bipartite_Graph(Graph _G,int _n,int _m){G=_G;n=_n;m=_m;k=G.m;}
		void ins(int x,int y){G.ins(x,y);}
		int Hungary(){
			int an=0;
			start();
			fr(i,n)if(fd(i,i))an++;
			fr(i,m)if(lky[i])lkx[lky[i]]=i;
			return an;
		}
		void print(){
			fr(i,m)if(lky[i])printf("%d - %d\n",lky[i],i);
		}
		pair<VI,VI> Minimum_Vertex_Coverage(){
			find();
			VI VL,VR;
			fr(i,n)if(lkx[i]&&!vl[i])VL.PB(i);
			fr(i,m)if(vr[i])VR.PB(i);
			return MP(VL,VR);
		}
		pair<VI,VI> Largest_Independent_Set(){
			find();
			VI VL,VR;
			fr(i,n)if(!lkx[i]||vl[i])VL.PB(i);
			fr(i,m)if(!vr[i])VR.PB(i);
			return MP(VL,VR);
		}
		pair<VI,VI> Maximum_Clique(){
			Bipartite_Graph W(Anti_Graph(G),n,m);
			return W.Largest_Independent_Set();
		}
};
