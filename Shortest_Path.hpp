//function : Solve the shortest path problem
//T - The type of weight edges
//n - The number of points
//S - The start vertex
//T d[i] - The distance from the vertex S to vertex i
//Weight_Graph<T>G - The weighted graph to solve
//Shortest_Path(n,S) - Make a Shortest_Path struct with n vertexs whose start vertex is S
//Shortest_Path(Weight_Graph<T>G,S) - Make a Shortest_Path struct base on Weight_Graph G and start vertex S
//void ins(x,y,z) - Add an edge from x to y with weight z
//void SPFA() - Use SPFA algorithim to solve the shortest path problem, which time complexity is O(nm)
//void Dijkstra() - Use optimazed Dijkstra algorithm to solve the shortest path problem, which time complexity is O(mlogm)
//bool nega_ring() - Check whether the nega ring exists in the graph, which time complexity is O(m)
//Weight_Graph<T> Shortest_Path_Topology() - Return all the edges in the shortest path, which make up a topology.
//void print() - Print the distance from the vertex S to each vertex
#include "Weight_Graph.hpp"
template<typename T> struct Shortest_Path{
	static const int N=111111;
	static const T inf=1e9;
	int S,n;
	T d[N];
	Weight_Graph<T>G;
	private:
		bool v[N];
		void start(){fr(i,n)d[i]=inf,v[i]=0;d[S]=0;}
		void dfs(int x){
			v[x]=1;int y;
			for(pair<int,T> o:G.V[x])if(d[x]+o.Y<d[y=o.X]){
				d[y]=d[x]+o.Y;
				if(v[y])return 1;
				dfs(y);
			}
			v[x]=0;
		}
	public:
		Shortest_Path(int _n,int _S):n(_n),S(_S){
			fr(i,n)d[i]=inf,v[i]=0;
			d[S]=0;
		}
		Shortest_Path(Weight_Graph<T>_G,int _S):S(_S){
			G=_G;n=G.n;
			fr(i,n)d[i]=inf,v[i]=0;
			d[S]=0;
		}
		void ins(int x,int y,T z){G.ins(x,y,z);}
		void SPFA(){
			int x,y;queue<int>Q;Q.push(S);start();
			for(d[S]=0;!Q.empty();v[x]=0,Q.pop())
				for(pair<int,T> o:G.V[x=Q.front()])
					if(d[x]+o.Y<d[y=o.X])
						if(d[y]=d[x]+o.Y,!v[y])
							v[y]=1,Q.push(y); 
		}
		void Dijkstra(){
			priority_queue<pair<T,int> >Q;int x,y;start();
			for(Q.push(MP(0,S));!Q.empty();v[x]=1)
				if(x=Q.top().Y,Q.pop(),!v[x])
					for(pair<int,T> o:G.V[x])
						if(d[x]+o.Y<d[y=o.X])
							d[y]=d[x]+o.Y,Q.push(MP(-d[y],y));
		}
		bool nega_ring(){
			fr(i,n)d[i]=v[i]=0;
			fr(i,n)if(dfs(i))return 1;
			return 0;
		}
		Weight_Graph<T> Shortest_Path_Topology(){
			Dijkstra();
			Weight_Graph<T> W(n);
			fr(x,n)for(pair<int,T> o:G.V[x])
				if(d[x]+o.Y==d[o.X])W.ins(x,o.X,o.Y);
			return W;
		}
		void print(){
			fr(i,n)cout<<d[i]<<i==n?'\n':' '; 
		}
};
