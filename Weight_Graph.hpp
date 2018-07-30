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
#include "Graph.hpp"
template<typename,const int> struct Weight_Graph;
template<typename T=LL,const int N=111111> ostream &operator<<(ostream &,const Weight_Graph<T,N> &);
template<typename T=LL,const int N=111111> istream &operator>>(istream &,Weight_Graph<T,N> &);
template<typename T=LL,const int N=111111> struct Weight_Graph{
	friend struct Graph;
	friend ostream &operator<< <T,N>(ostream &,const Weight_Graph<T,N> &);
	friend istream &operator>> <T,N>(istream &,Weight_Graph<T,N> &);
	int n,m;
	vector<pair<int,T> >V[N];
	Weight_Graph()=default;
	Weight_Graph(int _n=0):n(_n),m(0){}
	Weight_Graph(const Weight_Graph&G):n(G.n),m(G.m){fr(i,n)V[i]=G.V[i];}
	~Weight_Graph(){clear();}
	Weight_Graph &operator=(const Weight_Graph&G){
		if(this==&G)return *this;
		fr(i,n)V[i].clear();
		n=G.n;m=G.m;
		fr(i,n)V[i]=G.V[i];
		return *this;
	}
	Weight_Graph(Weight_Graph &&G)noexcept:n(G.n),m(G.m){fr(i,n)V[i].swap(G.V[i]);}
	Weight_Graph &operator=(Weight_Graph &&G)noexcept{
		n=G.n;m=G.m;
		fr(i,n)V[i].swap(G.V[i]);
		return *this;
	}
	void clear(){fr(i,n)V[i].clear();m=0;}
	void ins(int x,int y,T z){V[x].PB(MP(y,z));m++;}
	Graph To_Graph(){
		Graph G(n);
		fr(x,n)for(auto o:V[x])G.ins(x,o.X);
		return G;
	}
};
template<typename T=LL,const int N=111111>
ostream &operator<<(ostream &os,const Weight_Graph<T,N> &G){
	os<<"N = "<<G.n<<" , "<<"M = "<<G.m<<endl;
	fr(x,G.n)for(auto o:G.V[x])os<<x<<" -> "<<o.X<<" ["<<o.Y<<"]"<<endl;
	return os;
}
template<typename T=LL,const int N=111111>
istream &operator>>(istream &is,Weight_Graph<T,N> &G){
	is>>G.n>>G.m;
	int x,y;T z;
	fr(i,G.m)is>>x>>y>>z,G.ins(x,y,z);
	return is;
}
#endif
