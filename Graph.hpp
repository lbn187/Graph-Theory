//function: store a directed graph
//n - The number of vertexs
//m - The number of edges
//vector<int> V[N] - The vector to store edges
//Graph() - Make a graph with no vertexs or edges
//Graph(n) - Make a graph with no vertexs and no edges
//Graph(G) - Mkae the graph by copying the graph G
//Graph &operator=(const Graph&G) - Assignment the graph from G 
//Graph Anti_Graph(Graph G) - Get the anti-graph of G
#include "start.hpp"
struct Graph{
	int n,m;
	vector<int>V[N];
	Graph(){n=0;m=0;}
	Graph(int _n){
		n=_n;m=0;
		fr(i,n)V[i].clear();
	}
	Graph(const Graph &G){
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
	}
	~Graph(){fr(i,n)V[i].clear();}
	Graph &operator=(const Graph &G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
	}
	void ins(int x,int y){V[x].PB(y);m++;}//加入一条从x到y权值为z的边
};
Graph Anti_Graph(Graph G){
	bool *vs;
	vs=new bool[G.n+1];
	Graph _G;
	_G.n=G.n;
	_G.m=0;
	fr(i,G.n){
		fr(j,G.n)vs[j]=0;vs[i]=1;
		for(int x:G.V[i])vs[x]=1;
		fr(j,G.n)if(!vs[j])_G.ins(i,j);
	}
	return _G;
}
