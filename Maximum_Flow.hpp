//function - The struct to solve maximum flow problem
//Edge<T>{x,y,nxt,cap} - The template to store edges, which from x to y with flow z, which next edge is nxt
//udEdge<T>{x,y,mi,mx} - The template to store edges, which from x to y with minimum flow mi and maximum flow mx
//n - The number of vertex
//m - The number of edges
//s - The start vertex
//t - The terminate vertex
//Maximum_Flow(n,s=0,t=0) - Initial opeartion
//ins(x,y,z) - Add an edge from x to y with flow limit z
//dinic(s,t,n=0) - Use dinic algorithm to solve the maximum flow, the start vertex is s and the terminate vertex is t, which time complixity is O(n^2m). What's more, you can change the number of vertex to n.
//ISAP(s,t,n=0) -Use ISAP algorithm to solve the maximum flow, the start vertex is s and the terminate vertex is t, which time complixity is O(n^2m^(0.5)). What's more, you can change the number of vertex to n.
//Graph Residual_Graph() - Return the residual graph of the residual network
//VI Minimal_cut_set(st) -Return the minimal cut set belong to st
//vector<T> Updown_Feasible_Flow(vector<udEdge<T> >e,int n) - Return every edge's flow if udEdges has an updown feasible flow, or {} if not
//T Updown_Maximum_Feasible_Flow(vector<udEdge<T> >e,int n,int s,int t,vector<T>&AN) - Return the updown maximum feasible flow of udedges e with n vertex, start from s and terminate in t, store every edge's feasible flow in vector AN. If it's not feasible, return -1.
//T Updown_Minimum_Feasible_Flow(vector<udEdge<T> >e,int n,int s,int t,vector<T>&AN) - Return the updown minimum feasible flow of udedges e with n vertex, start from s and terminate in t, store every edge's feasible flow in vector AN. If it's not feasible, return -1.
#ifndef MAXIMUM_FLOW_HPP
#define MAXIMUM_FLOW_HPP
#include "Graph.hpp"
template<typename T> struct Edge{int x,y,nxt;T cap;};
template<typename T> struct Maximum_Flow{
	static const int N=1111;
	static const T INF=1e9;
	int n,m,s,t;
	int fir[N];
	vector<Edge<T> >e;
	private:
		int d[N],cur[N];
		bool vs[N];
		int pre[N],nb[N];
		bool bfs(){
			QI Q;CL(d);
			for(d[s]=1,Q.push(s);!Q.empty();){
				int x=Q.front();Q.pop();
				for(int i=fir[x],y;i;i=e[i].nxt)
					if(e[i].cap>0&&d[y=e[i].y]==0)
						d[y]=d[x]+1,Q.push(y);
			}
			return d[t]>0;
		}
		int dfs(int u,T fl){
			if(u==t)return fl;
			for(int& i=cur[u],y;i;i=e[i].nxt)
				if(d[y=e[i].y]==d[u]+1&&e[i].cap!=0){
					T z=dfs(y,min(fl,e[i].cap));
					if(z>0)return e[i].cap-=z,e[i^1].cap+=z,z;
				}
			return 0;
		}
		void bfs(int t){
			QI Q;fr(i,n)d[i]=n;
			for(d[t]=0,Q.push(t);!Q.empty();){
				int x=Q.front();Q.pop();
				for(int i=fir[x],y;i;i=e[i].nxt)
					if(e[i^1].cap>0&&d[y=e[i].y]==n)
						d[y]=d[x]+1,Q.push(y);
			}
		}
		void find(Graph&G,int x){
			if(vs[x])return;vs[x]=1;
			for(int y:G.V[x])find(G,y);
		}
	public:
		Maximum_Flow(int _n,int _s=0,int _t=0):n(_n),m(0),s(_s),t(_t){e.PB({0,0,0,0});e.PB({0,0,0,0});}
		void ins(int x,int y,T z){
			int id=e.size();
			e.PB({x,y,fir[x],z});fir[x]=id;
			e.PB({y,x,fir[y],0});fir[y]=id+1;
			m++;
		}
		T dinic(int _s,int _t,int _n=0){
			T an=0,d;s=_s;t=_t;if(_n)n=_n;
			for(;bfs();){
				fr(i,n)cur[i]=fir[i];
				for(;d=dfs(s,INF);)an+=d;
			}
			return an;
		}
		T ISAP(int _s,int _t,int _n=0){
			T V,fl=0;int u,v,i;if(_n)n=_n;
			s=_s;t=_t;CL(nb);CL(pre);
			bfs(t);
			fr(i,n)nb[d[i]]++,cur[i]=fir[i],pre[i]=0;
			for(u=s;d[s]<n;){
				if(u==t){
					for(V=INF,i=s;i!=t;i=e[cur[i]].y)
						if(e[cur[i]].cap<V)V=e[cur[u=i]].cap;
					for(fl+=V,i=s;i!=t;i=e[cur[i]].y)
						e[cur[i]].cap-=V,e[cur[i]^1].cap+=V;
				}
				for(i=cur[u];i;i=e[i].nxt)
					if(e[i].cap>0&&d[v=e[i].y]+1==d[u])break;
				if(i)cur[u]=i,pre[v]=u,u=v;else{
					if(!--nb[d[u]])break;
					for(i=cur[u]=fir[u],v=n;i;i=e[i].nxt)
						if(d[e[i].y]<v&&e[i].cap)v=d[e[i].y];
					++nb[d[u]=v+1];
					if(u!=s)u=pre[u];
				}
			}
			return fl;
		}
		Graph Residual_Graph(){
			Graph G(n);
			fr(x,n)for(int i=fir[x];i;i=e[i].nxt)
				if(e[i].cap>0)G.ins(x,e[i].y);
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
template<typename T> struct udEdge{int x,y;T mi,mx;};
template<class T> bool Updown_Feasible_Flow(vector<udEdge<T> >e,int n,vector<T>&AN){
	static const int N=1111;
	int ss=n+1,tt=n+2;
	Maximum_Flow<T> G(n+2);
	T du[N],sum=0;
	AN.clear();fr(i,n)du[i]=0;
	for(udEdge<T> o:e){
		G.ins(o.x,o.y,o.mx-o.mi);
		du[o.x]-=o.mi;du[o.y]+=o.mi;
		AN.PB(o.mi);
	}
	fr(i,n){
		if(du[i]>0)G.ins(ss,i,du[i]),sum+=du[i];
		if(du[i]<0)G.ins(i,tt,-du[i]);
	}
	if(G.ISAP(ss,tt,n+2)!=sum)return 0;else{
		for(int i=0;i<e.size();i++)AN[i]+=G.e[(i+1)*2+1].cap;
		return 1;
	}
}
template<class T> T Updown_Maximum_Feasible_Flow(vector<udEdge<T> >e,int n,int s,int t,vector<T> AN){
	static const int N=1111;
	static const T INF=1e9;
	int ss=n+1,tt=n+2;
	Maximum_Flow<T> G(n+2);
	T du[N],SUM=0;
	AN.clear();fr(i,n)du[i]=0;
	for(udEdge<T> o:e){
		G.ins(o.x,o.y,o.mx-o.mi);
		du[o.x]-=o.mi;du[o.y]+=o.mi;
		AN.PB(o.mi);
	}
	fr(i,n){
		if(du[i]>0)G.ins(ss,i,du[i]),SUM+=du[i];
		if(du[i]<0)G.ins(i,tt,-du[i]);
	}
	G.ins(t,s,INF);
	if(G.ISAP(ss,tt,n+2)!=SUM)return -1;else{
		G.fir[ss]=G.fir[tt]=0;
		T tmp=G.ISAP(s,t,n);
		for(int i=0;i<e.size();i++)AN[i]+=G.e[(i+1)*2+1].cap;
		return tmp;
	}
}
template<class T> T Updown_Minimum_Feasible_Flow(vector<udEdge<T> >e,int n,int s,int t,vector<T> AN){
	static const int N=1111;
	static const T INF=1e9;
	int ss=n+1,tt=n+2;
	Maximum_Flow<T> G(n+2);
	T du[N],SUM=0;
	AN.clear();fr(i,n)du[i]=0;
	for(udEdge<T> o:e){
		G.ins(o.x,o.y,o.mx-o.mi);
		du[o.x]-=o.mi;du[o.y]+=o.mi;
		AN.PB(o.mi);
	}
	fr(i,n){
		if(du[i]>0)G.ins(ss,i,du[i]),SUM+=du[i];
		if(du[i]<0)G.ins(i,tt,-du[i]);
	}
	G.dinic(ss,tt,n+2);
	G.ins(t,s,INF);
	G.dinic(ss,tt,n+2);
	bool ff=0;int i;
	for(i=G.fir[ss];i;i=G.e[i].nxt)if(G.e[i].cap>0)ff=1;
	if(ff)return -1;else{
		for(i=0;i<e.size();i++)AN[i]+=G.e[(i+1)*2+1].cap;
		for(i=G.fir[t];i;i=G.e[i].nxt)if(G.e[i].y==s)break;
		return G.e[i^1].cap;
	}
}
#endif
