//function: store a directed graph
//n - The number of vertexs
//m - The number of edges
//vector<int> V[N] - The vector to store edges
//Graph() - Make a graph with no vertexs or edges
//Graph(n) - Make a graph with no vertexs and no edges
//Graph(G) - Make the graph by copying the graph G
//Graph &operator=(const Graph&G) - Assignment the graph from G 
//void clear() - Clear all the edges
//void ins(int x,int y) - Add a edge from vertex x to vertex y
//void BFS(Graph G, int S) - Get BFS order from vertex S
//void Topological_Sorting(Graph G) - Make topological sorting
//Graph Anti_Graph(Graph G) - Get the anti-graph of G
#include "start.hpp"
struct Graph{
	static const int N=111111;
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
	~Graph(){clear();}
	Graph &operator=(const Graph &G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
	}
	void clear(){fr(i,n)V[i].clear();m=0;}
	void ins(int x,int y){V[x].PB(y);m++;}
	/*
	VI BFS(int S){
		VI E;queue<int>Q;bool v[N];
		fr(i,n)v[i]=0;
		Q.push(S);v[S]=1;
		for(;!Q.empty();){
			int x=Q.front();E.PB(x);Q.pop();
			for(int y:V[x])if(!v[y])v[y]=1,Q.push(y);
		}
		return E;
	}
	VI Topological_Sorting(){
		int du[N];VI E;queue<int>Q; 
		fr(i,n)du[i]=0;
		fr(x,n)for(int y:V[x])du[y]++;
		fr(i,n)if(!du[i])Q.push(i);
		for(;!Q.empty();){
			int x=Q.front();E.PB(x);Q.pop();
			for(int y:V[x])if(!--du[y])Q.push(y);
		}
		return E;
	}*/
};
VI BFS(Graph G,int S){
	VI E;queue<int>Q;bool v[N];
	fr(i,G.n)v[i]=0;
	Q.push(S);v[S]=1;
	for(;!Q.empty();){
		int x=Q.front();E.PB(x);Q.pop();
		for(int y:G.V[x])if(!v[y])v[y]=1,Q.push(y);
	}
	return E;
}
VI Topological_Sorting(Graph G){
	int du[N];VI E;queue<int>Q; 
	fr(i,G.n)du[i]=0;
	fr(x,G.n)for(int y:G.V[x])du[y]++;
	fr(i,G.n)if(!du[i])Q.push(i);
	for(;!Q.empty();){
		int x=Q.front();E.PB(x);Q.pop();
		for(int y:G.V[x])if(!--du[y])Q.push(y);
	}
	return E;
}
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
