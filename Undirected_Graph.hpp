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
	friend ostream &operator<<(ostream &,const Undirected_Graph&);
	friend istream &operator>>(istream &,Undirected_Graph&);
	static const int N=111111;
	int n,m;
	VI V[N];
	Undirected_Graph()=default;
	Undirected_Graph(int _n):n(_n),m(0){}
	Undirected_Graph(const Undirected_Graph &G):n(G.n),m(G.m){fr(i,n)V[i]=G.V[i];}
	~Undirected_Graph(){clear();}
	Undirected_Graph &operator=(const Undirected_Graph &G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
		return *this;
	}
	Undirected_Graph(Undirected_Graph &&G)noexcept:n(G.n),m(G.m){fr(i,n)V[i].swap(G.V[i]);}
	Undirected_Graph &operator=(Undirected_Graph &&G)noexcept{
		n=G.n;m=G.m;
		fr(i,n)V[i].swap(G.V[i]);
		return *this;
	}
	void clear(){fr(i,n)V[i].clear();m=0;}
	void ins(int x,int y){V[x].PB(y);V[y].PB(x);m++;}
	Graph To_Graph(){
		Graph G(n);
		fr(x,n)for(auto y:V[x])G.ins(x,y);
		return G;
	}
};
ostream &operator<<(ostream &os,const Undirected_Graph &G){
	os<<"N = "<<G.n<<" , "<<"M = "<<G.m<<endl;
	fr(x,G.n)for(auto y:G.V[x])if(x<=y)os<<x<<" --- "<<y<<endl;
	return os;
}
istream &operator>>(istream &is,Undirected_Graph &G){
	is>>G.n>>G.m;
	int x,y;
	fr(i,G.m)is>>x>>y,G.ins(x,y);
	return is;
}
#endif
