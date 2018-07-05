//function - The struct to solve maximum flow problem
//Edge<T>{x,y,nxt,cap} - the template to store edges, which from x to y with flow z, which next edge is nxt
//n - The number of vertex
//m - The number of edges
//s - The start vertex
//t - The terminate vertex
//Maxflow(n,s=0,t=0) - Initial opeartion
//ins(x,y,z) - Add an edge from x to y with flow limit z
//dinic(s,t) - Use dinic algorithm to solve the maximum flow, the start vertex is s and the terminate vertex is t, which time complixity is O(n^2m)
//ISAP(s,t) -Use ISAP algorithm to solve the maximum flow, the start vertex is s and the terminate vertex is t, which time complixity is O(n^2m^(0.5))
//Graph Residual_Graph() - Return the residual graph of the residual network
//VI Minimal_cut_set(st) -Return the minimal cut set belong to st
#include "Graph.hpp"
template<typename T> struct Edge{int x,y,nxt;T cap;};
template<typename T> struct Maximum_Flow{
	static const int N=555;
	static const T inf=1e9;
	int n,m,s,t;
	private:
		vector<Edge<T> >edge;
		int fir[N],d[N],cur[N];
		bool vs[N];
		int pre[N],nb[N];
		bool bfs(){
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
		int dfs(int u,T fl){
			if(u==t)return fl;
			for(int& i=cur[u],y;i;i=edge[i].nxt)
				if(d[y=edge[i].y]==d[u]+1&&edge[i].cap!=0){
					T z=dfs(y,min(fl,edge[i].cap));
					if(z>0)return edge[i].cap-=z,edge[i^1].cap+=z,z;
				}
			return 0;
		}
		void bfs(int t){
			queue<int>Q;
			fr(i,n)d[i]=n;
			d[t]=0;Q.push(t);
			for(;!Q.empty();){
				int x=Q.front();Q.pop();
				for(int i=fir[x],y;i;i=edge[i].nxt)
					if(edge[i^1].cap>0&&d[y=edge[i].y]==n)
						d[y]=d[x]+1,Q.push(y);
			}
		}
		void find(Graph&G,int x){
			if(vs[x])return;vs[x]=1;
			for(int y:G.V[x])find(G,y);
		}
	public:
		Maximum_Flow(int _n,int _s=0,int _t=0):n(_n),m(0),s(_s),t(_t){edge.PB({0,0,0,0});edge.PB({0,0,0,0});}
		void ins(int x,int y,T z){
			int id=edge.size();
			edge.PB({x,y,fir[x],z});fir[x]=id;
			edge.PB({y,x,fir[y],0});fir[y]=id+1;
			m++;
		}
		T dinic(int _s,int _t){
			T an=0,d;s=_s;t=_t;
			for(;bfs();){
				fr(i,n)cur[i]=fir[i];
				for(;d=dfs(s,inf);)an+=d;
			}
			return an;
		}
		T ISAP(int _s,int _t){
			T V,fl=0;int u,v,i;
			s=_s;t=_t;CL(nb);CL(pre);
			bfs(t);
			fr(i,n)nb[d[i]]++,cur[i]=fir[i],pre[i]=0;
			for(u=s;d[s]<n;){
				if(u==t){
					for(V=inf,i=s;i!=t;i=edge[cur[i]].y)
						if(edge[cur[i]].cap<V)V=edge[cur[u=i]].cap;
					for(fl+=V,i=s;i!=t;i=edge[cur[i]].y)
						edge[cur[i]].cap-=V,edge[cur[i]^1].cap+=V;
				}
				for(i=cur[u];i;i=edge[i].nxt)
					if(edge[i].cap>0&&d[v=edge[i].y]+1==d[u])break;
				if(i)cur[u]=i,pre[v]=u,u=v;else{
					if(!--nb[d[u]])break;
					for(i=cur[u]=fir[u],v=n;i;i=edge[i].nxt)
						if(d[edge[i].y]<v&&edge[i].cap)v=d[edge[i].y];
					++nb[d[u]=v+1];
					if(u!=s)u=pre[u];
				}
			}
			return fl;
		}
		Graph Residual_Graph(){
			Graph G(n);
			fr(x,n)
				for(int i=fir[x];i;i=edge[i].nxt)
					if(edge[i].cap>0)G.ins(x,edge[i].y);
			return G;
		}
		VI Minimal_cut_set(int st=0){
			VI V;Graph G=Residual_Graph();
			fr(i,n)vs[i]=0;
			find(G,st?st:s);
			fr(i,n)if(vs[i])V.PB(i);
			return V;
		}
};
