//function: store a directed weighted matrix graph
//n - The number of vertex
//T - The Type of weight 
//vector<vector<T> > a - The vector to store weighted edges
//Matrix_Graph() - Make a matrix graph with no vertexs or edges
//Matrix_Graph(n,z) - Make a matrix graph with n vertexs, and the initial value is z
//Matrix_Graph(G) - Make the matrix graph by copying the weighted graph G
//Matrix_Graph &operator=(const Matrix_Graph<T>&G) - Assignment the matrix graph from G
#include "start.hpp"
template<typename T> struct Matrix_Graph{
	int n;
	vector<vector<T> >a;
	Matrix_Graph(){n=0;a.clear();}
	Matrix_Graph(int _n,T z=0){
		n=_n;
		vector<T>tmp;a.PB(tmp);
		fr(i,n+1)tmp.PB(z);
		fr(i,n)a.PB(tmp);
	}
	Matrix_Graph(const Matrix_Graph<T>&G){
		n=G.n;
		fr(i,n)a[i]=G.a[i];
	}
	Matrix_Graph &operator=(const Matrix_Graph<T>&G){
		if(this==&G)return *this;
		fr(i,n)a[i].clear();
	}
	void ins(int x,int y,T z){a[x][y]=z;}
};
