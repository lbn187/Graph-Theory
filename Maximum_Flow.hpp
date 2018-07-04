//function - The struct to solve maximum flow problem
//Edge<T>{x,y,nxt,cap} - the template to store edges, which from x to y with flow z, which next edge is nxt
//n - The number of vertex
//m - The number of edges
//Maxflow() - Initial opeartion
//ins(x,y,z) - Add an edge from x to y with flow limit z
//dinic(s,t) - Use dinic to solve the maximum flow, the start vertex is s and the terminate vertex is t, which time complixity is O(V^2E)
#include "start.hpp"
template<typename T> struct Edge{int x,y,nxt;T cap;};
template<typename T> struct Maximum_Flow{
	static const int N=111;
	static const T inf=1e18;
	int n,m;
	private:
		vector<Edge<T> >edge;
		int fir[N],d[N],cur[N];
		bool bfs(int s,int t){
			queue<int>Q;CL(d);
			d[s]=1;Q.push(s);
			for(;!Q.empty();){
				int x=Q.front();Q.pop();
				for(int i=fir[x],y;i;i=edge[i].nxt)
					if(edge[i].cap>0&&d[y=edge[i].y]==0)
						d[y]=d[x]+1,Q.push(y);
			}
			return d[t]>0;
		}
		int dfs(int u,int t,T fl){
			if(u==t)return fl;
			for(int& i=cur[u],y;i;i=edge[i].nxt)
				if(d[y=edge[i].y]==d[u]+1&&edge[i].cap!=0){
					T z=dfs(y,t,min(fl,edge[i].cap));
					if(z>0)return edge[i].cap-=z,edge[i^1].cap+=z,z;
				}
			return 0;
		}
	public:
		Maximum_Flow(int _n):n(_n),m(0){edge.PB({0,0,0,0});edge.PB({0,0,0,0});}
		void ins(int x,int y,T z){
			int id=edge.size();
			edge.PB({x,y,fir[x],z});fir[x]=id;
			edge.PB({y,x,fir[y],0});fir[y]=id+1;
			m++;
		}
		T dinic(int s,int t){
			T an=0,d;
			for(;bfs(s,t);){
				fr(i,n)cur[i]=fir[i];
				for(;d=dfs(s,t,inf);)an+=d;
			}
			return an;
		}
};
