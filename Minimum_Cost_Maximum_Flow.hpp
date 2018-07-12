//funcion - The struct to solve minimum cost maximum flow problem
//Edge<T>{x,y,nxt,cap,co} - The template to store edges, which from x to y with flow z and cost co, which next edge is nxt
//n - The number of vertex
//m - The number of edges
//s - The start vertex
//t - The terminate vertex
//Minimum_Cost_Maximum_Flow(n,s=0,t=0) - Initial opeartion
//ins(x,y,cap,co) - Add an edge from x to y with flow limit cap and cost co
//pair<T1,T2> SPFA(int _s,int _t,int _n=0) - Use spfa force algorithm to solve the problem, and return the flow and cost
//pair<T1,T2> Dinic_SPFA(int _s,int _t,int _n=0) - Use spfa algorithm and dinic to solve the problem
//pair<T1,T2> Dijkstra(int _s,int _t,int _n=0) - Use dijkstra algorithm and dinic to solve the problem
//pair<T1,T2> ZKW(int _s,int_t,int _n=0) - Use ZKW algorithm to solve the problem
#ifndef MINIMUM_COST_MAXIMUM_FLOW_HPP
#define MINIMUM_COST_MAXIMUM_FLOW_HPP
#include "start.hpp"
template<typename T1,typename T2>struct CostEdge{int x,y,nxt;T1 cap;T2 co;};
template<typename T1,typename T2>struct Minimum_Cost_Maximum_Flow{
	static const int N=444;
	static const T1 INF1=2147483647;
	static const T2 INF2=1e18;
	int n,m,s,t,fir[N];
	vector<CostEdge<T1,T2> >e;
	private:
		T1 fl;T2 an,d[N];
		bool v[N];
		int pre[N],fa[N],cur[N];
		T2 h[N];
		bool spfa(){
			int x,y,i;QI Q;
			fr(i,n)d[i]=INF2,v[i]=0;
			d[s]=0;Q.push(s);v[s]=1;
			for(;!Q.empty();)
				for(i=fir[x=Q.front()],Q.pop(),v[x]=0;i;i=e[i].nxt)
					if(d[x]+e[i].co<d[y=e[i].y]&&e[i].cap>0)
						if(d[y]=d[fa[y]=x]+e[pre[y]=i].co,!v[y])v[y]=1,Q.push(y);
			return d[t]<INF2;
		}
		void end(){
			T1 p=INF1;int i;
			for(i=t;i!=s;i=fa[i])p=min(p,e[pre[i]].cap);
			for(fl+=p,i=t;i!=s;i=fa[i])e[pre[i]].cap-=p,e[pre[i]^1].cap+=p,an+=p*e[pre[i]].co;
		}
		bool _spfa(){
			int x,y,i;QI Q;
			fr(i,n)d[i]=INF2,v[i]=0;
			for(d[t]=0,Q.push(t),v[t]=1;!Q.empty();)
				for(i=fir[x=Q.front()],Q.pop(),v[x]=0;i;i=e[i].nxt)
					if(d[x]+e[i^1].co<d[y=e[i].y]&&e[i^1].cap>0)
						if(d[y]=d[x]+e[i^1].co,!v[y])v[y]=1,Q.push(y);
			return d[s]<INF2;
		}
		bool dij(){
			PQ<pair<T2,int> >Q;int i,x,y;T2 z,w;
			fr(i,n)d[i]=INF2;
			for(Q.push(MP(d[s]=0,s));!Q.empty();){
				x=Q.top().Y;z=-Q.top().X;Q.pop();
				if(d[x]!=z)continue;
				for(i=fir[x];i;i=e[i].nxt)if(e[i].cap>0){
					y=e[i].y;w=d[x]+h[x]-h[y]+e[i].co;
					if(w<d[y])d[y]=w,Q.push(MP(-d[y],y));
				}
			}
			fr(i,n)h[i]+=d[i];
			fr(i,n)if(h[i]>INF2)h[i]=INF2;
			return h[t]!=INF2;
		}
		T1 dfs(int x,T1 p){
			if(x==t||!p)return fl+=p,an+=p*h[t],p;
			int y;T1 w,tmp=0;v[x]=1;
			for(int &i=cur[x];i;i=e[i].nxt)
				if(!v[y=e[i].y]&&e[i].cap>0&&e[i].co+h[x]==h[y=e[i].y]){
					w=dfs(y,min(p-tmp,e[i].cap));
					tmp+=w;e[i].cap-=w;e[i^1].cap+=w;
					if(tmp==p)break;
				}
			v[x]=0;
			return tmp;
		}
		T1 aug(int x,T1 p){
			if(x==t)return fl+=p,an+=d[s]*p,p;
			v[x]=1;T1 tmp=0,w;
			for(int &i=cur[x],y;i;i=e[i].nxt)
				if(!v[y=e[i].y]&&e[i].cap>0&&d[x]==d[y]+e[i].co){
					w=aug(y,min(e[i].cap,p-tmp));
					e[i].cap-=w;e[i^1].cap+=w;tmp+=w;
					if(tmp==p)return tmp;
				}
			return tmp;
		}
		bool mdflabel(){
			T2 z=INF2;
			for(auto o:e)if(v[o.x]&&!v[o.y]&&o.cap>0)z=min(z,d[o.y]-d[o.x]+o.co);
			if(z==INF2)return 0;
			fr(i,n)if(v[i])d[i]+=z;
			return 1;
		}
	public:
		Minimum_Cost_Maximum_Flow(int _n,int _s=0,int _t=0):n(_n),m(0),s(_s),t(_t){e.PB({0,0,0,0,0});e.PB({0,0,0,0,0});}
		void ins(int x,int y,T1 cap,T2 co){
			int id=SZ(e);
			e.PB({x,y,fir[x],cap,co});fir[x]=id;
			e.PB({y,x,fir[y],0,-co});fir[y]=id+1;
			m++;
		}
		pair<T1,T2> SPFA(int _s,int _t,int _n=0){
			s=_s;t=_t;fl=0;an=0;if(_n)n=_n;
			for(;spfa();end());
			return MP(fl,an);
		}
		pair<T1,T2> Dinic_SPFA(int _s,int _t,int _n=0){
			s=_s;t=_t;fl=0;an=0;if(_n)n=_n;
			for(;_spfa();)for(CP(cur,fir);aug(s,INF1);CL(v));
			return MP(fl,an);
		}
		pair<T1,T2> Dijkstra(int _s,int _t,int _n=0){
			s=_s;t=_t;fl=0;an=0;if(_n)n=_n;
			for(CL(h),CL(v);dij();)CP(cur,fir),dfs(s,INF1);
			return MP(fl,an);
		}
		pair<T1,T2> ZKW(int _s,int _t,int _n=0){
			s=_s;t=_t;an=0;fl=0;CL(d);if(_n)n=_n;
			do do CL(v),CP(cur,fir);while(aug(s,INF1)>0);while(mdflabel());
			return MP(fl,an);
		}
};
#endif
