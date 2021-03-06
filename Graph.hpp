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
//Graph Transpose_Graph(Graph G) - Get the transpose graph of G
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "start.hpp"
struct Graph{
	friend VI BFS(Graph G,int S);
	friend VI Topological_Sorting(Graph G);
	friend Graph Anti_Graph(Graph G);
	friend ostream &operator<<(ostream &,const Graph&);
	friend istream &operator>>(istream &,Graph&);
	static const int N=111111;
	int n,m;
	VI V[N];
	Graph()=default;
	Graph(int _n):n(_n){}
	Graph(const Graph &G):n(G.n),m(G.m){fr(i,n)V[i]=G.V[i];}
	Graph &operator=(const Graph &G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
		return *this;
	}
	Graph(Graph &&G)noexcept:n(G.n),m(G.m){fr(i,n)V[i].swap(G.V[i]);}
	Graph &operator=(Graph &&G)noexcept{
		n=G.n;m=G.m;
		fr(i,n)V[i].swap(G.V[i]);
		return *this;
	}
	~Graph(){clear();}
	void init(int _n){n=_n;clear();}
	void clear(){fr(i,n)V[i].clear();m=0;}
	void ins(int x,int y){V[x].PB(y);m++;}
};
ostream &operator<<(ostream &os,const Graph &G){//重载输出
	os<<"N = "<<G.n<<" , "<<"M = "<<G.m<<endl;
	fr(x,G.n)for(auto y:G.V[x])os<<x<<" -> "<<y<<endl;
	return os;
}
istream &operator>>(istream &is,Graph &G){//重载输入
	is>>G.n>>G.m;
	int x,y;
	fr(i,G.m)is>>x>>y,G.ins(x,y);
	return is;
}
Graph Transpose_Graph(Graph G){//反图
	Graph _G(G.n);
	fr(x,G.n)for(int y:G.V[x])_G.ins(y,x);
	return _G;
}
Graph Anti_Graph(Graph G){//补图
	bool vs[G.N];
	Graph _G(G.n);
	fr(i,G.n){
		fr(j,G.n)vs[j]=0;vs[i]=1;
		for(int x:G.V[i])vs[x]=1;
		fr(j,G.n)if(!vs[j])_G.ins(i,j);
	}
	return _G;
}
VI BFS(Graph G,int S){
	VI E;QI Q;bool v[G.N];
	fr(i,G.n)v[i]=0;
	Q.PH(S);v[S]=1;
	for(;!Q.empty();){
		int x=Q.front();E.PB(x);Q.pop();
		for(int y:G.V[x])if(!v[y])v[y]=1,Q.PH(y);
	}
	return E;
}
VI Topological_Sorting(Graph G){
	int du[G.N];VI E;QI Q; 
	fr(i,G.n)du[i]=0;
	fr(x,G.n)for(int y:G.V[x])du[y]++;
	fr(i,G.n)if(!du[i])Q.PH(i);
	for(;!Q.empty();){
		int x=Q.front();E.PB(x);Q.pop();
		for(int y:G.V[x])if(!--du[y])Q.PH(y);
	}
	return E;
}
#endif
