//function: store a undirected graph
//n - The number of vertexs
//m - The number of edges
//vector<int> V[N] - The vector to store edges
//Undirected_Graph() - Make a graph with no vertexs or edges
//Undirected Graph(n) - Make a graph with no vertexs and no edges
//Undirected Graph(G) - Make the graph by copying the graph G
//Undirected Graph &operator=(const Graph&G) - Assignment the graph from G 
//void clear() - Clear all the edges
//void ins(int x,int y) - Add a edge link vertex x and vertex y
#ifndef UNDIRECTED_GRAPH_HPP
#define UNDIRECTED_GRAPH_HPP
#include "start.hpp"
struct Undirected_Graph{
	static const int N=111111;
	int n,m;
	vector<int>V[N];
	Undirected_Graph(int _n=0):n(_n),m(0){fr(i,n)V[i].clear();}
	Undirected_Graph(const Undirected_Graph &G):n(G.n),m(G.m){fr(i,n)V[i]=G.V[i];}
	~Undirected_Graph(){clear();}
	Undirected_Graph &operator=(const Undirected_Graph &G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
	}
	void clear(){fr(i,n)V[i].clear();m=0;}
	void ins(int x,int y){V[x].PB(y);V[y].PB(x);m++;}
};
#endif
