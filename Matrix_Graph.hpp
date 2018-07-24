//function: store a directed weighted matrix graph
//n - The number of vertex
//T - The Type of weight 
//vector<vector<T> > a - The vector to store weighted edges
//Matrix_Graph() - Make a matrix graph with no vertexs or edges
//Matrix_Graph(n,z) - Make a matrix graph with n vertexs, and the initial value is z
//Matrix_Graph(G) - Make the matrix graph by copying the weighted graph G
//Matrix_Graph &operator=(const Matrix_Graph<T>&G) - Assignment the matrix graph from G
#ifndef MATRIX_GRAPH_HPP
#define MATRIX_GRAPH_HPP
#include "start.hpp"
template<typename T> struct Matrix_Graph{
	static const int N=1111;
	int n;
	T a[N][N];
	Matrix_Graph()=default;
	Matrix_Graph(int _n,T z=0):n(_n){
		fr(i,n)fr(j,n)a[i][j]=z;
	}
	Matrix_Graph(const Matrix_Graph<T>&G):n(G.n){
		fr(i,n)fr(j,n)a[i][j]=G.a[i][j];
	}
	Matrix_Graph &operator=(const Matrix_Graph<T>&G){
		if(this==&G)return *this;
		fr(i,n)fr(j,n)a[i][j]=G.a[i][j];
		return *this;
	}
	void clear(){
		fr(i,n)fr(j,n)a[i][j]=0;
	}
	void ins(int x,int y,T z){a[x][y]=z;}
};
#endif
