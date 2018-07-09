//function: store a directed weighted graph
//n - The number of points
//m - The number of edges
//T - The Type of weight 
//vector<pair<int,T> > V[N] - The vector to store weighted edges
//Weight_Graph() - Make a weighted graph with no vertexs or edges
//Weight_Graph(n) - Make a weighted graph with no vertexs and no edges
//Weight_Graph(G) - Mkae the weithted graph by copying the weighted graph G
//Weight_Graph &operator=(const Weight_Graph<T>&G) - Assignment the weighted graph from G
#ifndef WEIGHT_GRAPH_HPP
#define WEIGHT_GRAPH_HPP
#include "start.hpp"
template<typename T> struct Weight_Graph{
	static const int N=111111;
	int n,m;
	vector<pair<int,T> >V[N];
	Weight_Graph(int _n=0):n(_n),m(0){fr(i,n)V[i].clear();}
	Weight_Graph(const Weight_Graph<T>&G):n(G.n),m(G.m){fr(i,n)V[i]=G.V[i];}
	~Weight_Graph(){fr(i,n)V[i].clear();}
	Weight_Graph &operator=(const Weight_Graph<T>&G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
	}
	void ins(int x,int y,T z){V[x].PB(MP(y,z));m++;}
};
#endif
